//
// Created by javst on 2/7/2021.
//

#ifndef TTMMPYINTEGRATION_LOG_H
#define TTMMPYINTEGRATION_LOG_H

#include <iostream>
#include <string>

void print(std::string out){
    std::cout <<  out << std::endl;
}

void log(std::string scriptName, std::string out){
    std::cout << "FROM " << scriptName << ": "<<  out << std::endl;
}

#endif //TTMMPYINTEGRATION_LOG_H
