#include <iostream>
#include <pybind11/pybind11.h>
#include <Python.h>

#include "memaccess.hpp"
#include "log.hpp"
#include "map.hpp"
#include "characters.hpp"


void defineKeys(pybind11::module_& m){
    m.attr("VK_Q") = pybind11::int_('Q');
    m.attr("VK_W") = pybind11::int_('W');
    m.attr("VK_E") = pybind11::int_('E');
    m.attr("VK_R") = pybind11::int_('R');
    m.attr("VK_T") = pybind11::int_('T');
    m.attr("VK_Y") = pybind11::int_('Y');
    m.attr("VK_U") = pybind11::int_('U');
    m.attr("VK_I") = pybind11::int_('I');
    m.attr("VK_O") = pybind11::int_('O');
    m.attr("VK_P") = pybind11::int_('P');

    m.attr("VK_A") = pybind11::int_('A');
    m.attr("VK_S") = pybind11::int_('S');
    m.attr("VK_D") = pybind11::int_('D');
    m.attr("VK_F") = pybind11::int_('F');
    m.attr("VK_G") = pybind11::int_('G');
    m.attr("VK_H") = pybind11::int_('H');
    m.attr("VK_J") = pybind11::int_('J');
    m.attr("VK_K") = pybind11::int_('K');
    m.attr("VK_L") = pybind11::int_('L');

    m.attr("VK_Z") = pybind11::int_('Z');
    m.attr("VK_X") = pybind11::int_('X');
    m.attr("VK_C") = pybind11::int_('C');
    m.attr("VK_V") = pybind11::int_('V');
    m.attr("VK_B") = pybind11::int_('B');
    m.attr("VK_N") = pybind11::int_('N');
    m.attr("VK_M") = pybind11::int_('M');

    m.attr("VK_1") = pybind11::int_('1');
    m.attr("VK_2") = pybind11::int_('2');
    m.attr("VK_3") = pybind11::int_('3');
    m.attr("VK_4") = pybind11::int_('4');
    m.attr("VK_5") = pybind11::int_('5');
    m.attr("VK_6") = pybind11::int_('6');
    m.attr("VK_7") = pybind11::int_('7');
    m.attr("VK_8") = pybind11::int_('8');
    m.attr("VK_9") = pybind11::int_('9');
    m.attr("VK_0") = pybind11::int_('0');

    m.attr("VK_F1") = pybind11::int_(VK_F1);
    m.attr("VK_F2") = pybind11::int_(VK_F2);
    m.attr("VK_F3") = pybind11::int_(VK_F3);
    m.attr("VK_F4") = pybind11::int_(VK_F4);
    m.attr("VK_F5") = pybind11::int_(VK_F5);
    m.attr("VK_F6") = pybind11::int_(VK_F6);
    m.attr("VK_F7") = pybind11::int_(VK_F7);
    m.attr("VK_F8") = pybind11::int_(VK_F8);
    m.attr("VK_F9") = pybind11::int_(VK_F9);
    m.attr("VK_F10") = pybind11::int_(VK_F10);

    m.attr("VK_TAB") = pybind11::int_(VK_TAB);
    m.attr("VK_LCONTROL") = pybind11::int_(VK_LCONTROL);
    m.attr("VK_LSHIFT") = pybind11::int_(VK_LSHIFT);
    m.attr("VK_RCONTROL") = pybind11::int_(VK_RCONTROL);
    m.attr("VK_RSHIFT") = pybind11::int_(VK_RSHIFT);
    m.attr("VK_DELETE") = pybind11::int_(VK_DELETE);
    m.attr("VK_SPACE") = pybind11::int_(VK_SPACE);
    m.attr("VK_BACKSPACE") = pybind11::int_(VK_BACK);
    m.attr("VK_CAPSLOCK") = pybind11::int_(VK_CAPITAL);

    m.attr("VK_UP") = pybind11::int_(VK_UP);
    m.attr("VK_DOWN") = pybind11::int_(VK_DOWN);
    m.attr("VK_LEFT") = pybind11::int_(VK_LEFT);
    m.attr("VK_RIGHT") = pybind11::int_(VK_RIGHT);

}

PYBIND11_MODULE(TTMMScriptingLibrary, m) {
    m.doc() = "TTMM Scripting Engine"; // optional module docstring
    m.def("readInt", &readInt, "Reads the given integer from game memory");
    m.def("readShort", &readShort, "Reads the given short from game memory");
    m.def("readByte", &readByte, "Reads the given byte from game memory");
    m.def("readFloat", &readFloat, "Reads the given float from game memory");
    m.def("readString", &readString, "Reads the given null-terminated string from game memory");
    m.def("readBytes", &readBytes, "Reads a byte array of the given size from game memory");

    m.def("writeInt", &writeInt, "Writes the given integer into game memory");
    m.def("writeByte", &writeByte, "Writes the given byte into game memory");
    m.def("writeShort", &writeShort, "Writes the given byte into game memory");
    m.def("writeFloat", &writeFloat, "Writes the given float into game memory");
    m.def("writeString", &writeString, "Writes the given null-terminated string into game memory");
    m.def("writeBytes", &writeBytes, "Writes the given byte array into game memory");

    m.def("print", &print, "Writes the given string to the log output");
    m.def("log", &log, "Writes the given string to the log output in a filterable and searchable manner. This should be used when writing logs in production mods.");

    m.def("getCurrentMapName", &getCurrentMapName, "Gets the name of the currently loaded map.");
    m.def("getCurrentMapDirectory", &getCurrentMapDirectory, "Gets the name of the currently loaded map.");
    m.def("getCurrentMapPtr", &getCurrentMapPtr, "Gets a pointer to the currently loaded map.");

    m.def("getPlayerOnePtr", &getPlayerOnePtr, "Gets a pointer to player one's character.");
    m.def("getPlayerTwoPtr", &getPlayerTwoPtr, "Gets a pointer to player two's character.");

    m.def("getCreaturePosition", &getCreaturePosition, "Gets the position, as a tuple of floats, of the given character. This function is safe as it does a null check before retrieving memory.");
    m.def("getCreatureVelocity", &getCreatureVelocity, "Gets the velocity, as a tuple of floats, of the given character. This function is safe as it does a null check before retrieving memory.");

    m.def("setCreaturePosition", &setCreaturePosition, "Sets the position, as a tuple of floats, of the given character. This function is safe as it does a null check before retrieving memory.");
    m.def("setCreatureVelocity", &setCreatureVelocity, "Sets the velocity, as a tuple of floats, of the given character. This function is safe as it does a null check before retrieving memory.");

    defineKeys(m);
}
