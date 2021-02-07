
#include <windows.h>
#include <Python.h>
#include <string>
#include <algorithm>
#include "boost/filesystem.hpp"

inline bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

void runScript(std::string name){
    PyObject *pName, *pModule, *pFunc, *pValue;
    pName = PyUnicode_FromString((char*)name.c_str());
    pModule = PyImport_Import(pName);
    pFunc = PyObject_GetAttrString(pModule, (char*)"init");
    PyObject_CallObject(pFunc, nullptr);
}

void init(){

    Py_Initialize();
    PyRun_SimpleString("import sys");
    std::string path = "MODSCRIPTS";

    boost::filesystem::path apk_path(path);
    boost::filesystem::recursive_directory_iterator end;
    for (boost::filesystem::recursive_directory_iterator i(apk_path); i != end; ++i)
   {

       const boost::filesystem::path cp = (*i);
       auto path = cp.string();

       if(ends_with(path, ".py")){
           std::string module = path.substr(0, path.length() - 3);
           std::replace(module.begin(), module.end(), '\\', '.');

           runScript(module);
       }
    }

    Py_Finalize();
}

__declspec (dllexport) BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            init();
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
