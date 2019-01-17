//
// Created on 2018/12/12.
//

#ifndef PROGRAM_STRUCT_H
#define PROGRAM_STRUCT_H

#include <string>

struct _Point { //チャート上の各ポイントに相当
    double x;
    double y;
    double height = 0;
    double velocity = 0;
    double holdv = 0;
    double canhold = 0;
    int size = 0;
    _Point *next;
    int round;
};

struct _State { //飛行機の状態を示す
    double x;       //x座標
    double y;       //y座標
    double velocity;    //速度
    double height;      //高度[m]
    double direction;

    double Crusing_Distance;    //航続距離

    struct _Point *nextPoint;
    int ARRIVED;

    int Turning;
    int phase;
    double initialdir;
    double initialx;
    double initialy;
    std::string callsign;
    std::string from;
    int tag;
};

struct _Memory {    //世界の情報を示す
    int Wind_direction; //南0北1
    int Wait_order;
};

void printState(struct _State *state, int i);

void Change_Branch();

void Initialize_Airplane();

void Initialize_Memory();

void Initialize_Point();

#endif //PROGRAM_STRUCT_H
