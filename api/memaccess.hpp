//
// Created by javst on 2/7/2021.
//

#ifndef TTMMPYINTEGRATION_MEMACCESS_HPP
#define TTMMPYINTEGRATION_MEMACCESS_HPP

#include <iostream>
#include <pybind11/pybind11.h>
#include <Python.h>
#include <string>
#include <windows.h>

int setMemoryPerms(int addr, int size, int perms){
    int last = 0;
    VirtualProtect((void*)addr, (SIZE_T)size, (DWORD)perms, (PDWORD)(&last));
    return last;
}

unsigned char readByte(int addr){
    auto last = setMemoryPerms(addr, 4, PAGE_EXECUTE_READWRITE);
    unsigned char val =  *((unsigned char *) addr);
    setMemoryPerms(addr, 4, last);
    return val;
}

int readInt(int addr){
    auto last = setMemoryPerms(addr, 4, PAGE_EXECUTE_READWRITE);
    auto ret =  *((int *)addr);
    setMemoryPerms(addr, 4, last);
    return ret;
}

short readShort(int addr){
    auto last = setMemoryPerms(addr, 4, PAGE_EXECUTE_READWRITE);
    auto ret =  *((short *)addr);
    setMemoryPerms(addr, 4, last);
    return ret;
}

float readFloat(int addr){
    auto last = setMemoryPerms(addr, 4, PAGE_EXECUTE_READWRITE);
    auto ret =  *((float *)addr);
    setMemoryPerms(addr, 4, last);
    return ret;
}

std::string readString(int addr){
    auto last = setMemoryPerms(addr, 4, PAGE_EXECUTE_READWRITE);
    std::string newStr((char *) addr, strlen((char *) addr));
    setMemoryPerms(addr, 4, last);
    return newStr;
}

pybind11::bytes readBytes(int addr, int len){
    auto last = setMemoryPerms(addr, 4, PAGE_EXECUTE_READWRITE);
    pybind11::bytes bytes((char*) addr, len);
    setMemoryPerms(addr, 4, last);
    return bytes;
}

void writeInt(int addr, int val){
    auto last = setMemoryPerms(addr, 4, PAGE_EXECUTE_READWRITE);
    *((int *)addr) = val;
    setMemoryPerms(addr, 4, last);
}

void writeShort(int addr, short val){
    auto last = setMemoryPerms(addr, 4, PAGE_EXECUTE_READWRITE);
    *((short *)addr) = val;
    setMemoryPerms(addr, 4, last);
}

void writeByte(int addr, unsigned char byte){
    auto last = setMemoryPerms(addr, 4, PAGE_EXECUTE_READWRITE);
    *((unsigned char *)addr) = byte;
    setMemoryPerms(addr, 4, last);
}

void writeFloat(int addr, float val){
    auto last = setMemoryPerms(addr, 4, PAGE_EXECUTE_READWRITE);
    *((float *)addr) = val;
    setMemoryPerms(addr, 4, last);
}

void writeString(int addr, std::string val){
    auto last = setMemoryPerms(addr, 4, PAGE_EXECUTE_READWRITE);
    int size = val.length();
    memcpy((void*)addr, val.c_str(), size);
    setMemoryPerms(addr, 4, last);
}

void writeBytes(int addr,  pybind11::bytes bytes){
    auto last = setMemoryPerms(addr, 4, PAGE_EXECUTE_READWRITE);
    std::string strCpy = bytes;
    int len = strCpy.size();
    memcpy((void*)addr, strCpy.c_str(), len);
    setMemoryPerms(addr, 4, last);
}

#endif //TTMMPYINTEGRATION_MEMACCESS_HPP
