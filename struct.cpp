//
// Created on 2018/12/12.
//

#include "struct.hpp"
#include "main.hpp"
#include "func.hpp"
#include <stdio.h>
#include <math.h>

extern struct _State Airplane[N];
extern struct _Point ARRON, AWARD, ADDUM, RJTT;
extern struct _Point STONE, COLOR, CURRY, COUPE, CUTIE, CREAM, CLOAK, CAMEL, CACAO;    //北風・北東からくる便
extern struct _Point BRITZ, BRASS, BACON, BIBLO, BEAST, BONDO, LOC;  //南風・南西からくる便・ADDUMから続く
extern struct _Point DREAD, DENNY, DATUM, DYUKE, BONUS;  //南風・北東からくる便・STONEから続く
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

    RJTT.x = 168;
    RJTT.y = -63;
    RJTT.height = 150;
    RJTT.velocity = toDot(265.0);
    RJTT.next = NULL;

    ARRON.x = 234;
    ARRON.y = 55;
    ARRON.height = 1560;
    ARRON.velocity = 0; //RJTTを参照
    ARRON.next = &RJTT;

    AWARD.x = 290;
    AWARD.y = 152;
    AWARD.height = 3200;
    AWARD.velocity = toDot(440.0);
    AWARD.next = &ARRON;

    ADDUM.x = 317;
    ADDUM.y = 199;
    ADDUM.height = 0;//AWARDを参照
    ADDUM.velocity = 0;//AWARDを参照
    if (Memory.Wind_direction) {
        ADDUM.next = &AWARD;
    } else {
        ADDUM.next = &BRITZ;
    }

    BRITZ.x = 350;
    BRITZ.y = 107;
    BRITZ.height =
    BRITZ.velocity =
    BRITZ = &BRASS;

    BRASS.x = 322;
    BRASS.y = -2;
    BRASS.height
    BRASS.velocity
    BRASS.next = &BACON;

    BACON.x = 308;
    BACON.y = -55;
    BACON.height
    BACON.velocity
    BACON.next = &BIBLO;

    BIBLO.x = 300;
    BIBLO.y = -74;
    BIBLO.height
    BIBLO.velocity
    BIBLO.next = &BEAST;

    BEAST.x = 285;
    BEAST.y = -83;
    BEAST.height
    BEAST.velocity;
    BEAST.next = &BONDO;

    BONDO.x = 265;
    BONDO.y = -72;
    BONDO.height
    BONDO.velocity
    BONDO.next = &LOC;

    LOC.x = 184;
    LOC.y = -84;
    LOC.height = 0;
    LOC.velocity = 0;
    LOC.next = &RJTT;

    STONE.x = 323;
    STONE.y = -345;
    STONE.height
    STONE.velocity
    STONE.next = &COLOR;

    COLOR.x = 309;
    COLOR.y = -262;
    COLOR.height
    COLOR.velocity
    COLOR.next = &CURRY;

    CURRY.x = 311;
    CURRY.y = -105;
    CURRY.height
    CURRY.velocity
    CURRY.next = &COUPE;

    COUPE.x = 312;
    COUPE.y = -98;
    COUPE.height
    COUPE.velocity
    COUPE.next = &CUTIE;

    CUTIE.x = 320;
    CUTIE.y = -32;
    CUTIE.height
    CUTIE.velocity
    CUTIE.next = &CREAM;

    CREAM.x = 279;
    CREAM.y = 32;
    CREAM.height
    CREAM.velocity
    CREAM.next = &CLOAK;

    CLOAK.x = 255;
    CLOAK.y = 46;
    CLOAK.height
    CLOAK.velocity
    CLOAK.next = &CAMEL;

    CAMEL.x = 228;
    CAMEL.y = 32;
    CAMEL.height
    CAMEL.velocity
    CAMEL.next = &CACAO;

    CACAO.x = 216;
    CACAO.y = 6;
    CACAO.height
    CACAO.velocity
    CACAO.next = &RJTT;

    DREAD
    DREAD
    DREAD
    DREAD
    DREAD

    DENNY
    DENNY
    DENNY
    DENNY
    DENNY

    DATUM
    DATUM
    DATUM
    DATUM
    DATUM

    DYUKE
    DYUKE
    DYUKE
    DYUKE
    DYUKE

    BONUS
    BONUS
    BONUS
    BONUS
    BONUS
};

void Initialize_Memory() {
    Memory.Wind_direction = 0;
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
        Airplane[i].Delay = 0;
        Airplane[i].Crusing_Distance = 0;
        Airplane[i].nextPoint = &ADDUM;
        Airplane[i].ARRIVED = 0;
        Airplane[i].Turning = 0;
        Airplane[i].phase = 0;
        Airplane[i].initialdir = 0.0;
        Airplane[i].initialx = 0.0;
        Airplane[i].initialy = 0.0;
        lastphase[i] = 0;
    }
}