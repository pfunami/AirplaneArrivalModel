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

void printState(struct _State *state, int i) {
    printf("AIRPLANE code [%d]>>>\tat : ", i);
    if (state->ARRIVED) {
        printf("\tARRIVED.");
    }
    printf("\nPOSITION : (%f,%f)\tVELOCITY : %fkm/h\tHEIGHT : %fm\tDIRECTION : %fπrad\t\tCRUISINGDIST : %fkm\n",
           state->x, state->y, toKm(state->velocity), state->height, (-state->direction) / M_PI,
           state->Crusing_Distance);
    printf("\n");
}

void Change_Branch() {
    if (Memory.Wind_direction) { ADDUM.next = &AWARD; } else { ADDUM.next = &BRITZ; }
    if (Memory.Wind_direction) { STONE.next = &COLOR; } else { STONE.next = &DREAD; }
}

void Initialize_Point() {

    RJTT.x = 168;
    RJTT.y = -63;
    RJTT.height = 150;
    RJTT.velocity = toDot(265.0);
    RJTT.holdv = RJTT.velocity; //ヌルポインタ対策
    RJTT.next = NULL;

    ARRON.x = 234;
    ARRON.y = 55;
    ARRON.holdv = toDot(425.96);
    ARRON.canhold = 1;    //左1右-1できない0
    ARRON.next = &RJTT;

    AWARD.x = 290;
    AWARD.y = 152;
    AWARD.next = &ARRON;

    ADDUM.x = 280;
    ADDUM.y = 231;
    ADDUM.height = 3048;
    ADDUM.velocity = toDot(425.96);
    ADDUM.holdv = toDot(463);
    ADDUM.canhold = 1;

    BRITZ.x = 350;
    BRITZ.y = 107;
    BRITZ.next = &BRASS;

    BRASS.x = 322;
    BRASS.y = -2;
    BRASS.holdv = toDot(444.48);
    BRASS.canhold = 1;
    BRASS.next = &BACON;

    BACON.x = 308;
    BACON.y = -55;
    BACON.height = 2133.6;
    BACON.holdv = toDot(444.48);
    BACON.canhold = 1;
    BACON.next = &BIBLO;

    BIBLO.x = 300;
    BIBLO.y = -71;
    BIBLO.height = 2133.6;
    BIBLO.next = &BEAST;

    BEAST.x = 287;
    BEAST.y = -80;
    BEAST.height = 1676.4;
    BEAST.next = &BONDO;

    BONDO.x = 265;
    BONDO.y = -83;
    BONDO.height = 1524;
    BONDO.next = &LOC;

    LOC.x = 184;
    LOC.y = -81;
    LOC.next = &RJTT;

    STONE.x = 323;
    STONE.y = -345;
    STONE.height = 3352.8;
    STONE.velocity = toDot(463);
    STONE.holdv = toDot(463);
    STONE.canhold = -1;

    COLOR.x = 309;
    COLOR.y = -262;
    COLOR.next = &CURRY;

    CURRY.x = 307;
    CURRY.y = -194;
    CURRY.holdv = toDot(444.48);
    CURRY.canhold = -1;
    CURRY.next = &COUPE;

    COUPE.x = 312;
    COUPE.y = -98;
    COUPE.height = 2438.4;
    COUPE.next = &CUTIE;

    CUTIE.x = 320;
    CUTIE.y = -32;
    CUTIE.next = &CREAM;

    CREAM.x = 279;
    CREAM.y = 32;
    CREAM.holdv = toDot(444.48);
    CREAM.canhold = 1;
    CREAM.next = &CLOAK;

    CLOAK.x = 255;
    CLOAK.y = 46;
    CLOAK.next = &CAMEL;

    CAMEL.x = 228;
    CAMEL.y = 32;
    CAMEL.next = &CACAO;

    CACAO.x = 216;
    CACAO.y = 6;
    CACAO.holdv = toDot(425.96);
    CACAO.canhold = -1;
    CACAO.next = &RJTT;

    DREAD.x = 241;
    DREAD.y = -258;
    DREAD.height = 2438.4;
    DREAD.holdv = toDot(444.48);
    DREAD.canhold = -1;
    DREAD.next = &DENNY;

    DENNY.x = 275;
    DENNY.y = -185;
    DENNY.holdv = toDot(444.48);
    DENNY.canhold = -1;
    DENNY.next = &DATUM;

    DATUM.x = 292;
    DATUM.y = -139;
    DATUM.height = 1524;
    DATUM.next = &DYUKE;

    DYUKE.x = 295;
    DYUKE.y = -94;
    DYUKE.next = &BONUS;

    BONUS.x = 276;
    BONUS.y = -84;
    BONUS.height = 1524;
    BONUS.holdv = toDot(425.96);
    BONUS.canhold = -1;
    BONUS.next = &BONDO;
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
    Airplane[1].velocity = toDot(600.0);
    Airplane[1].height = 7000;
    Airplane[1].direction = atan2(ADDUM.y - Airplane[1].y,
                                  ADDUM.x - Airplane[1].x);
    for (int i = 0; i < N; ++i) {
        Airplane[i].Delay = 0;
        Airplane[i].Crusing_Distance = 0;
        Airplane[i].nextPoint = &STONE;
        Airplane[i].ARRIVED = 0;
        Airplane[i].Turning = 0;
        Airplane[i].phase = 0;
        Airplane[i].initialdir = 0.0;
        Airplane[i].initialx = 0.0;
        Airplane[i].initialy = 0.0;
        lastphase[i] = 0;
    }
}