#include <GLUT/glut.h>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include "main.hpp"
#include "func.hpp"
#include "method.hpp"
#include "display.hpp"


struct _State Airplane[N];
struct _Point A, ARRON, AWARD, ADDUM, RJTT, RJTTnr, RJTTnl, RJTTsr, RJTTsl;    //北風・南西からくる便
struct _Point STONE, COLOR, CURRY, COUPE, CUTIE, CREAM, CLOAK, CAMEL, CACAO;    //北風・北東からくる便
struct _Point BLITZ, BRASS, BACON, BIBLO, BEAST, BONDO, LOC;  //南風・南西からくる便・ADDUMから続く
struct _Point DREAD, DENNY, DATUM, DYUKE, BONUS;  //南風・北東からくる便・STONEから続く
extern struct _Memory Memory;

int TIME[3] = {0, 25, 16};
int count = 0, witch = 0;
extern int ORDER;

double NewDire;
double pre_x, pre_y, dPos = 0;
double RemainingDist, RDsub, velAcce, dropAcce;
double origin;
double straightDist = 15;
int sss = 0;

void JudgeState() {
    count++;
    if (ORDER) {
        Memory.Wait_order = !Memory.Wait_order;
        ORDER = 0;
    }
    int area[6];
    for (int i = 0; i < N; ++i) {
        if (!Airplane[i].ARRIVED) {
            dPos = Airplane[i].velocity;
            RemainingDist = sqrt(pow(Airplane[i].nextPoint->x - Airplane[i].x, 2) +
                                 pow(Airplane[i].nextPoint->y - Airplane[i].y, 2));
            ///*航続距離の更新*///----------------------------------------------------------------------------------------
            Airplane[i].Crusing_Distance += dPos;
            //----------------------------------------------------------------------------------------------------------


            ///*高度の更新*///-------------------------------------------------------------------------------------------
            origin = Airplane[i].height;
            struct _Point *point;
            double pre_h = Airplane[i].height;
            if (!Airplane[i].Turning) {
                point = Airplane[i].nextPoint;
                RDsub = RemainingDist;
                while (point->height == 0) {
                    RDsub += sqrt(pow(point->x - point->next->x, 2)
                                  + pow(point->y - point->next->y, 2));
                    point = point->next;
                }

                dropAcce = (point->height - Airplane[i].height) / RDsub;
                if (dropAcce * dPos < DropAcceMax) {
                    Airplane[i].height += DropAcceMax;
                } else {
                    Airplane[i].height += dropAcce * dPos;
                }
            }
            //----------------------------------------------------------------------------------------------------------


            ///*角度の更新*///-------------------------------------------------------------------------------------------
            origin = Airplane[i].direction;
            NewDire = atan2(Airplane[i].nextPoint->y - Airplane[i].y, Airplane[i].nextPoint->x - Airplane[i].x);
            double pre_d = Airplane[i].direction;
            if (!Airplane[i].Turning) {
                if (NewDire - origin > 0) {
                    if (maxDirection() < NewDire - origin && 2 * M_PI - maxDirection() > NewDire - origin) {
                        if (NewDire - origin <= M_PI) { Airplane[i].direction += maxDirection(); }
                        else { Airplane[i].direction -= maxDirection(); }
                    } else {
                        Airplane[i].direction = NewDire;
                    }
                } else if (NewDire - origin < 0) {
                    if (-maxDirection() > NewDire - origin && -2 * M_PI + maxDirection() < NewDire - origin) {
                        if (NewDire - origin <= -M_PI) {
                            Airplane[i].direction += maxDirection();
                        } else { Airplane[i].direction -= maxDirection(); }
                    } else {
                        Airplane[i].direction = NewDire;
                    }
                }
            } else {
                if (Airplane[i].phase == 1) {
                    if (abs(Airplane[i].direction - Airplane[i].initialdir) < M_PI) {
                        Airplane[i].direction -= Airplane[i].nextPoint->canhold * maxDirection();
                    } else {
                        Airplane[i].direction = Airplane[i].initialdir - Airplane[i].nextPoint->canhold * M_PI;
                        Airplane[i].phase = 2;
                        Airplane[i].initialx = Airplane[i].x;
                        Airplane[i].initialy = Airplane[i].y;
                    }
                } else if (Airplane[i].phase == 3) {
                    if (abs(Airplane[i].direction - Airplane[i].initialdir) < 2 * M_PI) {
                        Airplane[i].direction -= Airplane[i].nextPoint->canhold * maxDirection();
                    } else {
                        Airplane[i].direction = atan2(Airplane[i].nextPoint->y - Airplane[i].y,
                                                      Airplane[i].nextPoint->x - Airplane[i].x);
                        Airplane[i].phase = 4;
                        Airplane[i].initialx = Airplane[i].x;
                        Airplane[i].initialy = Airplane[i].y;
                    }
                }
            }
            //----------------------------------------------------------------------------------------------------------

            ///*速度の更新*///-------------------------------------------------------------------------------------------
            double pre_v = Airplane[i].velocity;
            if (!Airplane[i].Turning) {
                point = Airplane[i].nextPoint;
                RDsub = RemainingDist;
                if (!Memory.Wait_order) {
                    while (point->velocity == 0) {
                        RDsub += sqrt(pow(point->x - point->next->x, 2)
                                      + pow(point->y - point->next->y, 2));
                        point = point->next;
                    }
                    velAcce = (point->velocity - Airplane[i].velocity) / RDsub;
                } else {
                    while (point->holdv == 0) {
                        RDsub += sqrt(pow(point->x - point->next->x, 2)
                                      + pow(point->y - point->next->y, 2));
                        point = point->next;
                    }
                    velAcce = (point->holdv - Airplane[i].velocity) / RDsub;
                }
                if (velAcce * dPos < VelocityAcceMax) {
                    Airplane[i].velocity += VelocityAcceMax;
                } else {
                    Airplane[i].velocity += velAcce * dPos;
                }
            }
            //----------------------------------------------------------------------------------------------------------


            ///*座標の更新と領域チェック*///-------------------------------------------------------------------------------
            pre_x = Airplane[i].x;
            pre_y = Airplane[i].y;
            Airplane[i].x += Airplane[i].velocity * cos(Airplane[i].direction);
            Airplane[i].y += Airplane[i].velocity * sin(Airplane[i].direction);

            CheckTerritory(&Airplane[i], &Airplane[0], i, area);
            while (!area[0]) {
//                printf("速度調整\n");
                if (!(area[1] || area[2] || area[3] || area[4]) && area[5]) {
                    Airplane[i].velocity = pre_v;
                    Airplane[i].x = pre_x + Airplane[i].velocity * cos(Airplane[i].direction);
                    Airplane[i].y = pre_y + Airplane[i].velocity * sin(Airplane[i].direction);
                    break;
                } else { Airplane[i].velocity -= toDot(1); }
                Airplane[i].x = pre_x + Airplane[i].velocity * cos(Airplane[i].direction);
                Airplane[i].y = pre_y + Airplane[i].velocity * sin(Airplane[i].direction);
                if (abs(Airplane[i].velocity - pre_v) < abs(VelocityAcceMax)) {
                    break;
                }
                CheckTerritory(&Airplane[i], &Airplane[0], i, area);
            }
            while (!area[0]) {
                if (area[5] || area[3] || area[4]) {
                    Airplane[i].height = pre_h;
                    break;
                } else {
                    Airplane[i].height -= 0.1;
//                    printf("高度調整\n");
                }
                if (abs(DropAcceMax) <= abs(Airplane[i].height - pre_h)) { break; }
                CheckTerritory(&Airplane[i], &Airplane[0], i, area);
            }

            extern double expect_d;
            while (!area[0] && !area[5]) {
//                printf("角度調整\n");
                if ((area[1] || area[4]) && (area[2] || area[3])) {
                    if (abs(expect_d - pre_d) > maxDirection()) {
                        if (expect_d > pre_d) { Airplane[i].direction = pre_d + maxDirection(); }
                        else { Airplane[i].direction = pre_d - maxDirection(); }
                    } else {
                        Airplane[i].direction = expect_d;
                        Airplane[i].x = pre_x + Airplane[i].velocity * cos(Airplane[i].direction);
                        Airplane[i].y = pre_y + Airplane[i].velocity * sin(Airplane[i].direction);
                        break;
                    }
                } else {
                    if (area[1] || area[4]) { Airplane[i].direction -= M_PI / 540.0; }
                    else if (area[2] || area[3]) { Airplane[i].direction += M_PI / 540.0; }
                }
                Airplane[i].x = pre_x + Airplane[i].velocity * cos(Airplane[i].direction);
                Airplane[i].y = pre_y + Airplane[i].velocity * sin(Airplane[i].direction);
                if (abs(Airplane[i].direction - pre_d) > maxDirection()) { break; }
                CheckTerritory(&Airplane[i], &Airplane[0], i, area);
            }


            if (Airplane[i].Turning &&
                sqrt(pow(Airplane[i].initialx - Airplane[i].x, 2) +
                     pow(Airplane[i].initialy - Airplane[i].y, 2)) >= straightDist) {
                if (Airplane[i].phase == 2) {
                    Airplane[i].phase = 3;
                }
            }
            //----------------------------------------------------------------------------------------------------------


            ///*次の目標ポイントの更新*///---------------------------------------------------------------------------------
            if (RemainingDist <= 10) {
                if (Airplane[i].nextPoint->next == nullptr) {
                    printf("[%d] ARRIVED!\n", i);
                    printState(&Airplane[i], i);
                    Airplane[i].ARRIVED = 1;
                } else {
                    if (Memory.Wait_order && !Airplane[i].Turning) {
                        if (Airplane[i].nextPoint->canhold != 0) {
                            ChangeWaitOrder(&Memory.Wait_order, &Airplane[i].phase, &Airplane[i].Turning);
                            Airplane[i].nextPoint->size += 1;
                            Airplane[i].tag = Airplane[i].nextPoint->size;
                            Airplane[i].initialdir = Airplane[i].direction;
                            Airplane[i].Turning = 1;
                        } else {
                            Airplane[i].nextPoint = Airplane[i].nextPoint->next;
                        }
                    } else if (!Memory.Wait_order && Airplane[i].Turning) {
                        Airplane[i].nextPoint = Airplane[i].nextPoint->next;
                        ChangeWaitOrder(&Memory.Wait_order, &Airplane[i].phase, &Airplane[i].Turning);
                    } else if (!Memory.Wait_order && !Airplane[i].Turning) {
                        if (Airplane[i].nextPoint->next == &RJTT || Airplane[i].nextPoint->next == &LOC) {
                            std::string s = Airplane[i].callsign.substr(0, 3);
                            if (Memory.Wind_direction) {//北風
                                if (s == "JAL" || s == "SKY") { Airplane[i].nextPoint = &RJTTnl; }
                                else { Airplane[i].nextPoint = &RJTTnr; }
                            } else {
                                if (s == "JAL" || s == "SKY") { Airplane[i].nextPoint = &LOC; }
                                else { Airplane[i].nextPoint = &RJTTsl; }
                            }
                        } else {
                            Airplane[i].nextPoint = Airplane[i].nextPoint->next;
                        }
                    } else if (Memory.Wait_order && Airplane[i].Turning) {
                        Airplane[i].phase = 1;
                    }
                }
            }
            //----------------------------------------------------------------------------------------------------------
        }
    }

    TimePlus();
}

int main(int argc, char *argv[]) {
    Initialize_Memory();
    Initialize_Point();
    Initialize_Airplane();
    //opengl----
//    for (int i = 0; i < 100000; ++i) {
//        JudgeState();
//    }
    OpenGL_main(argc, &argv[0]);

    return 0;
}