//
// Created on 2018/12/12.
//

#include "struct.h"
#include "main.h"
#include "func.h"
#include <stdio.h>
#include <math.h>

extern struct _State Airplane[N];
extern struct _Point ARRON, AWARD, ADDUM, RJTT;
extern struct _Memory Memory;

extern int lastphase[N];

void printState(struct _State *state) {
    for (int i = 0; i < N; ++i) {
        printf("AIRPLANE code [%d]>>>", i);
        if (state[i].ARRIVED) {
            printf("\tARRIVED.");
        }
        printf("\nPOSITION : (%f,%f)\tVELOCITY : %fkm/h\tHEIGHT : %fm\tDIRECTION : %fπrad\tDELAY : %fmin\tCRUISINGDIST : %fkm\n",
               state[i].x, state[i].y, toKm(state[i].velocity), state[i].height, -state[i].direction / M_PI,
               state[i].Delay, state[i].Crusing_Distance);
    }
    printf("\n");
}

void Initialize_Point() {

    RJTT.x = DestinationX;
    RJTT.y = DestinationY;
    RJTT.height = 150;
    RJTT.velocity = toDot(265.0);
    RJTT.next = NULL;

    ARRON.x = 237;
    ARRON.y = 154;
    ARRON.height = 1560;
    ARRON.velocity = 0; //RJTTを参照
    ARRON.next = &RJTT;

    AWARD.x = 258;
    AWARD.y = 192;
    AWARD.height = 3200;
    AWARD.velocity = toDot(440.0);
    AWARD.next = &ARRON;

    ADDUM.x = 248;
    ADDUM.y = 234;
    ADDUM.height = 0;//AWARDを参照
    ADDUM.velocity = 0;//AWARDを参照
    ADDUM.next = &AWARD;
};

void Initialize_Memory() {
    Memory.Weather = 0;
    Memory.Landable = 1;
    Memory.Wind_direction = 1;
    Memory.Wait_order = 0;
}

void Initialize_Airplane() {    //試験的に２機のみ
    Airplane[0].x = 200;
    Airplane[0].y = 242;
    Airplane[0].velocity = toDot(600.0);
    Airplane[0].height = 5000;
    Airplane[0].direction = atan2(ADDUM.y - Airplane[0].y,
                                  ADDUM.x - Airplane[0].x);

    Airplane[1].x = 160;
    Airplane[1].y = 270;
    Airplane[1].velocity = toDot(600.0);;
    Airplane[1].height = 7000;
    Airplane[1].direction = atan2(ADDUM.y - Airplane[1].y,
                                  ADDUM.x - Airplane[1].x);
    for (int i = 0; i < N; ++i) {
        Airplane[i].isEmergency = 0;
        Airplane[i].Delay = 0;
        Airplane[i].Crusing_Distance = 0;
        Airplane[i].Comfort = 0;
        Airplane[i].nextPoint = &ADDUM;
        Airplane[i].ARRIVED = 0;
        Airplane[i].Turning = 0;
        Airplane[i].phase = 1;
        Airplane[i].initialdir = 0.0;
        Airplane[i].initialx = 0.0;
        Airplane[i].initialy = 0.0;
        lastphase[i] = 0;
    }
}