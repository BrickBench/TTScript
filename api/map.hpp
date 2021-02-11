//
// Created by javst on 2/8/2021.
//

#ifndef TTMMPYINTEGRATION_MAP_H
#define TTMMPYINTEGRATION_MAP_H

#include <string>

int getCurrentMapPtr(){
    return *((int*) 0x00802c54);
}

std::string getCurrentMapName(){
    if(getCurrentMapPtr() == 0) return "";
    return std::string (((char*) getCurrentMapPtr()));
}

std::string getCurrentMapDirectory(){
    if(getCurrentMapPtr() == 0) return "";
    return std::string (((char*) getCurrentMapPtr() + 128));

}

#endif //TTMMPYINTEGRATION_MAP_H
