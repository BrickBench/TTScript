
#include <windows.h>
#include <Python.h>
#include <string>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include "boost/filesystem.hpp"

static const unsigned int NumberOfKeys = 256U;

bool previousKeyboardState[NumberOfKeys];

static std::vector<std::tuple<std::string, PyObject*>> scripts;

static int replacedUpdateCall = 0;
static int replacedInitCall = 0;

typedef void (* repFn)();

static bool firstRun = true;

inline bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

void checkPythonErrors(){
    if(PyErr_Occurred() != NULL) {
        PyObject *pyExcType;
        PyObject *pyExcValue;
        PyObject *pyExcTraceback;
        PyErr_Fetch(&pyExcType, &pyExcValue, &pyExcTraceback);
        PyErr_NormalizeException(&pyExcType, &pyExcValue, &pyExcTraceback);

        PyObject* str_exc_type = PyObject_Repr(pyExcType);
        PyObject* pyStr = PyUnicode_AsEncodedString(str_exc_type, "utf-8", "Error ~");
        const char *strExcType =  PyBytes_AS_STRING(pyStr);

        PyObject* str_exc_value = PyObject_Repr(pyExcValue);
        PyObject* pyExcValueStr = PyUnicode_AsEncodedString(str_exc_value, "utf-8", "Error ~");
        const char *strExcValue =  PyBytes_AS_STRING(pyExcValueStr);

        std::cout << "Python error: " << strExcType << " " << strExcValue << std::endl;

        Py_XDECREF(pyExcType);
        Py_XDECREF(pyExcValue);
        Py_XDECREF(pyExcTraceback);

        Py_XDECREF(str_exc_type);
        Py_XDECREF(pyStr);

        Py_XDECREF(str_exc_value);
        Py_XDECREF(pyExcValueStr);
    }
}

void execInit(const std::string& name, PyObject *module){

    std::cout << "Executing script " << name << std::endl;
    PyObject *pFunc = PyObject_GetAttrString(module, (char*)"init");

    PyObject* ret =  PyObject_CallFunction(pFunc, nullptr);
    if(ret == NULL){
        std::cout << "Error encountered while running " << name << std::endl;
        checkPythonErrors();
    }else{
        Py_DECREF(ret);
    }
    Py_DECREF(pFunc);

}


void init(){
    auto replacedFunc = (repFn)replacedInitCall;

    (*replacedFunc)();

    std::cout << "Setting Python runtime location" << std::endl;

    Py_SetPythonHome(L"Python");

    std::cout << "Initializing Python runtime" << std::endl;

    Py_Initialize();

    PyRun_SimpleString("import sys");

    std::cout << "Reading scripts" << std::endl;


    std::string path = "MODSCRIPTS";

    boost::filesystem::path apk_path(path);
    boost::filesystem::recursive_directory_iterator end;

    std::cout << "Loading directory "<< path << std::endl;

    for (boost::filesystem::recursive_directory_iterator i(apk_path); i != end; ++i)
    {
        const boost::filesystem::path cp = (*i);
        auto path = cp.string();

        if(ends_with(path, ".py")){
            std::string module = path.substr(0, path.length() - 3);
            std::cout << "Found script " << module << std::endl;

            std::replace(module.begin(), module.end(), '\\', '.');

            PyObject *pName, *pModule, *pFunc;
            pName = PyUnicode_FromString((char*)module.c_str());
            pModule = PyImport_Import(pName);

            scripts.emplace_back(std::make_tuple(module, pModule));
        }
    }

    std::cout << "Initializing modules..." << std::endl;

    for(auto const& value: scripts){
        execInit(std::get<0>(value), std::get<1>(value));
    }
}

void execUpdate(const std::string& name, PyObject *module){
    PyObject *pFunc = PyObject_GetAttrString(module, (char*)"update");
    PyObject* ret =  PyObject_CallFunction(pFunc, nullptr);
    if(ret == NULL){
        std::cout << "Error encountered while running " << name << std::endl;
        checkPythonErrors();
    }else{
        Py_DECREF(ret);
    }
    Py_DECREF(pFunc);
}

void execKeyPress(const std::string& name, PyObject *module, int key, bool pressed){
    PyObject *pFunc = pressed ? PyObject_GetAttrString(module, (char*)"onKeyPressed") : PyObject_GetAttrString(module, (char*)"onKeyReleased");
    if(pFunc == NULL) return;
    PyObject *charInt = Py_BuildValue("i", key);
    PyObject *pArgs = PyTuple_New(1);
    PyTuple_SetItem(pArgs, 0, charInt);
    PyObject* ret =  PyObject_CallObject(pFunc, pArgs);
    if(ret == NULL){
        std::cout << "Error encountered while running " << name << std::endl;
        checkPythonErrors();
    }else{
        Py_DECREF(ret);
    }
    Py_DECREF(pArgs);
    Py_DECREF(pFunc);
    Py_DECREF(charInt);

}

void rescanKeys(){
    for (unsigned int keyNum = 0U; keyNum < NumberOfKeys; ++keyNum)
    {
        bool newState = (GetAsyncKeyState(keyNum) & (1 << 16));
        if(newState != previousKeyboardState[keyNum]){
            previousKeyboardState[keyNum] = newState;
            for(auto const& value: scripts){
                execKeyPress(std::get<0>(value), std::get<1>(value), keyNum, newState);
            }
        }
    }
}


void update(){
    auto replacedFunc = (repFn)replacedUpdateCall;

    (*replacedFunc)();

    if(firstRun){
        std::cout << "Beginning injected update" << std::endl;
        firstRun = false;
    }

    rescanKeys();

    for(auto const& value: scripts){
        execUpdate(std::get<0>(value), std::get<1>(value));
    }
}

void end(){
    std::cout << "Finalizing script engine" << std::endl;
    Py_Finalize();
}

int setMemoryPerms(int addr, int size, int perms){
    int last = 0;
    VirtualProtect((void*)addr, (SIZE_T)size, (DWORD)perms, (PDWORD)(&last));
    return last;
}

int injectFunction(int targetInstruction, void * func){
    int reljmp = (int)func - (targetInstruction + 5);
    int replacementOffset = targetInstruction + 1;

    auto last = setMemoryPerms(targetInstruction, 8, PAGE_EXECUTE_READWRITE);

    int replacedCall = *((int*)replacementOffset) + (targetInstruction + 5);
    *((int*)replacementOffset) = reljmp;

    setMemoryPerms(targetInstruction, 8, last);

    return replacedCall;
}

void openConsole(){
    AllocConsole();
    freopen("script.log", "w", stdout);
    freopen("script.log", "w", stderr);
    freopen("CON", "r", stdin); // Note: "r", not "w".
}

void runInjection(){
    openConsole();

    const int initInstruction = 0x00492c89;
    std::cout << "Injecting intialization function at instruction " << std::hex << initInstruction << std::dec << std::endl;
    replacedInitCall = injectFunction(initInstruction, (void*)&init);

    const int updateInstruction = 0x004933d4;
    std::cout << "Injecting runtime function at instruction " << std::hex << updateInstruction << std::dec << std::endl;
    replacedUpdateCall = injectFunction(updateInstruction, (void*)&update);

    std::cout << "Completed injection, DLL thread ending"<< std::endl;

}

__declspec (dllexport) BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            runInjection();
            break;
        case DLL_PROCESS_DETACH:
            //Py_Initialize();
            break;
        case DLL_THREAD_ATTACH:
            break;
        case DLL_THREAD_DETACH:
            break;
        default:
            break;
    }

    return TRUE;
}
