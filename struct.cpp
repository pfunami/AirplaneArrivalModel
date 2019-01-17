//
// Created on 2018/12/12.
//

#include "struct.hpp"
#include "main.hpp"
#include "func.hpp"
#include <cstdio>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

extern struct _State Airplane[N];
extern struct _Point A, ARRON, AWARD, ADDUM, RJTT, RJTTnr, RJTTnl, RJTTsr, RJTTsl;
extern struct _Point STONE, COLOR, CURRY, COUPE, CUTIE, CREAM, CLOAK, CAMEL, CACAO;    //北風・北東からくる便
extern struct _Point BLITZ, BRASS, BACON, BIBLO, BEAST, BONDO, LOC;  //南風・南西からくる便・ADDUMから続く
extern struct _Point DREAD, DENNY, DATUM, DYUKE, BONUS;  //南風・北東からくる便・STONEから続く
extern struct _Memory Memory;

void printState(struct _State *state, int k) {
    printf("AIRPLANE code [%d]>>>", k);
    if (state->ARRIVED) {
        printf("\tARRIVED.");
    }
    printf("\nPOSITION : (%f,%f)\tVELOCITY : %fkm/h\tHEIGHT : %fm\tDIRECTION : %fπrad\t\tCRUISINGDIST : %fkm\n",
           state->x, state->y, toKm(state->velocity), state->height, (-state->direction) / M_PI,
           state->Crusing_Distance);
    printf("\n");
}

void Change_Branch() {
    if (Memory.Wind_direction) { ADDUM.next = &AWARD; } else { ADDUM.next = &BLITZ; }
    if (Memory.Wind_direction) { STONE.next = &COLOR; } else { STONE.next = &DREAD; }
}

void Initialize_Point() {

    RJTT.x = 168;
    RJTT.y = -63;
    RJTT.height = 150;
    RJTT.velocity = toDot(265.0);
    RJTT.holdv = RJTT.velocity; //ヌルポインタ対策
    RJTT.next = nullptr;

    RJTTnl.x = 169;
    RJTTnl.y = -56;
    RJTTnr.x = 175;
    RJTTnr.y = -59;
    RJTTsl.x = 182;
    RJTTsl.y = -57;
    RJTTsr.x = 167;
    RJTTsr.y = -68;
    RJTTnl.height = RJTTnr.height = RJTTsl.height = RJTTsr.height = RJTT.height;
    RJTTnl.velocity = RJTTnr.velocity = RJTTsl.velocity = RJTTsr.velocity = RJTT.velocity;
    RJTTnl.holdv = RJTTnr.holdv = RJTTsl.holdv = RJTTsr.holdv = RJTT.holdv;
    RJTTnl.next = RJTTnr.next = RJTTsl.next = RJTTsr.next = nullptr;

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

    A.x = 226;
    A.y = 265;
    A.next = &ADDUM;

    BLITZ.x = 350;
    BLITZ.y = 107;
    BLITZ.next = &BRASS;

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
    LOC.next = &RJTTsr;

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

void Initialize_Airplane() {
    using namespace std;
    //csvから航空機情報を読み込み
    ifstream ifs("data2.csv");
    if (!ifs) {
        cout << "Error! File can not be opened" << endl;
        exit(1);
    }
    string data[N][8];
    string str = "";
    int i = 0, j = 0;
    // ファイルの中身を一行ずつ読み取る
    while (getline(ifs, str)) {
        string tmp = "";
        istringstream stream(str);
        // 区切り文字がなくなるまで文字を区切っていく
        while (getline(stream, tmp, ',')) {
            // 区切られた文字がtmpに入る
            data[i][j] = tmp;
            j++;
        }
        j = 0;
        i++;
    }
    for (int k = 0; k < N; ++k) {
        Airplane[k].x = atof(data[k][0].c_str());
        Airplane[k].y = atof(data[k][1].c_str());
        Airplane[k].velocity = toDot(atof(data[k][2].c_str()));
        Airplane[k].height = atof(data[k][3].c_str());
        if (data[k][4] == "RJTT") { Airplane[k].nextPoint = &RJTT; }
        else if (data[k][4] == "ARLON") { Airplane[k].nextPoint = &ARRON; }
        else if (data[k][4] == "AWARD") { Airplane[k].nextPoint = &AWARD; }
        else if (data[k][4] == "ADDUM") { Airplane[k].nextPoint = &ADDUM; }
        else if (data[k][4] == "BLITZ") { Airplane[k].nextPoint = &BLITZ; }
        else if (data[k][4] == "BRASS") { Airplane[k].nextPoint = &BRASS; }
        else if (data[k][4] == "BACON") { Airplane[k].nextPoint = &BACON; }
        else if (data[k][4] == "BIBLO") { Airplane[k].nextPoint = &BIBLO; }
        else if (data[k][4] == "BEAST") { Airplane[k].nextPoint = &BEAST; }
        else if (data[k][4] == "BONDO") { Airplane[k].nextPoint = &BONDO; }
        else if (data[k][4] == "LOC") { Airplane[k].nextPoint = &LOC; }
        else if (data[k][4] == "STONE") { Airplane[k].nextPoint = &STONE; }
        else if (data[k][4] == "COLOR") { Airplane[k].nextPoint = &COLOR; }
        else if (data[k][4] == "CURRY") { Airplane[k].nextPoint = &CURRY; }
        else if (data[k][4] == "COUPE") { Airplane[k].nextPoint = &COUPE; }
        else if (data[k][4] == "CUTIE") { Airplane[k].nextPoint = &CUTIE; }
        else if (data[k][4] == "CREAM") { Airplane[k].nextPoint = &CREAM; }
        else if (data[k][4] == "CLOAK") { Airplane[k].nextPoint = &CLOAK; }
        else if (data[k][4] == "CAMEL") { Airplane[k].nextPoint = &CAMEL; }
        else if (data[k][4] == "CACAO") { Airplane[k].nextPoint = &CACAO; }
        else if (data[k][4] == "DREAD") { Airplane[k].nextPoint = &DREAD; }
        else if (data[k][4] == "DENNY") { Airplane[k].nextPoint = &DENNY; }
        else if (data[k][4] == "DATUM") { Airplane[k].nextPoint = &DATUM; }
        else if (data[k][4] == "DYUKE") { Airplane[k].nextPoint = &DYUKE; }
        else if (data[k][4] == "BONUS") { Airplane[k].nextPoint = &BONUS; }
        else if (data[k][4] == "A") { Airplane[k].nextPoint = &A; }
        else {
            printf("%d???\n", k);
            exit(1);
        }
        Airplane[k].callsign = data[k][5];
        Airplane[k].from = data[k][6];
        Airplane[k].direction = atan2(Airplane[k].nextPoint->y - Airplane[k].y,
                                      Airplane[k].nextPoint->x - Airplane[k].x);
        Airplane[k].Crusing_Distance = 0;
        Airplane[k].ARRIVED = 0;
        Airplane[k].Turning = 0;
        Airplane[k].phase = 0;
        Airplane[k].initialdir = 0.0;
        Airplane[k].initialx = 0.0;
        Airplane[k].initialy = 0.0;
    }
}