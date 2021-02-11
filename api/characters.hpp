//
// Created by javst on 2/8/2021.
//

#ifndef TTMMPYINTEGRATION_CHARACTERS_H
#define TTMMPYINTEGRATION_CHARACTERS_H

int getPlayerOnePtr(){
    return *((int*)0x0093d810);
}

int getPlayerTwoPtr(){
    return *((int*)0x0093d814);
}

std::tuple<float, float, float> getCreaturePosition(int creaturePtr){
    if(creaturePtr == 0) return std::make_tuple(0.0f, 0.0f, 0.0f);
    return std::make_tuple(*((float*)(creaturePtr + 0x5c)), *((float*)(creaturePtr + 0x60)), *((float*)(creaturePtr + 0x64)));
}

std::tuple<float, float, float> getCreatureVelocity(int creaturePtr){
    if(creaturePtr == 0) return std::make_tuple(0.0f, 0.0f, 0.0f);
    return std::make_tuple(*((float*)(creaturePtr + 0x68)), *((float*)(creaturePtr + 0x6c)), *((float*)(creaturePtr + 0x70)));
}

void setCreaturePosition(int creaturePtr, std::tuple<float, float, float> &pos){
    if(creaturePtr == 0) return;
    *((float*)(creaturePtr + 0x5c)) = std::get<0>(pos);
    *((float*)(creaturePtr + 0x60)) = std::get<1>(pos);
    *((float*)(creaturePtr + 0x64)) = std::get<2>(pos);
}

void setCreatureVelocity(int creaturePtr, std::tuple<float, float, float> &pos){
    if(creaturePtr == 0) return;
    *((float*)(creaturePtr + 0x68)) = std::get<0>(pos);
    *((float*)(creaturePtr + 0x6c)) = std::get<1>(pos);
    *((float*)(creaturePtr + 0x70)) = std::get<2>(pos);
}

#endif //TTMMPYINTEGRATION_CHARACTERS_H
