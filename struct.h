//
// Created on 2018/12/12.
//

#ifndef PROGRAM_STRUCT_H
#define PROGRAM_STRUCT_H

struct _Point { //エンルートチャート上の各ポイントに相当
    double x;
    double y;
    double height;
    double velocity;
    _Point *next;
};

struct _State { //飛行機の状態を示す
    double x;       //x座標
    double y;       //y座標
    double velocity;    //速度
    double height;      //高度[m]
    double direction;

    int isEmergency;    //緊急事態

    double Delay;   //遅れ
    double Crusing_Distance;    //航続距離

    int Comfort;  //快適度

    struct _Point *nextPoint;
    int ARRIVED;

    int Turning;
    double initialdir;
};

struct _Memory {    //世界の情報を示す
    int Weather;
    int Landable;
    int Wind_direction; //南0北1
    int Wait_order;
};

void printState(struct _State *state);

void Initialize_Airplane();

void Initialize_Memory();

void Initialize_Point();

#endif //PROGRAM_STRUCT_H