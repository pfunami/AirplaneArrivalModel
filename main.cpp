#include <GLUT/glut.h>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <vector>
#include "main.hpp"
#include "func.hpp"
#include "struct.hpp"
#include "display.hpp"

struct _State Airplane[N];
struct _Point ARRON, AWARD, ADDUM, RJTT;
struct _Memory Memory;

int TIME[3] = {0, 0, 16};
int count = 0, lastphase[N];
extern int ORDER;

double NewDire;
double New_x, New_y, dPos = 0;
double RemainingDist, RDsub, velAcce, dropAcce;
double origin;
double straightDist = 15;

void JudgeState() {
    count++;
    if (ORDER) {
        Memory.Wait_order = !Memory.Wait_order;
        for (int i = 0; i < N; ++i) {
            lastphase[i] = Airplane[i].phase;
            if (Airplane[i].phase == 4 || Airplane[i].phase == 0)
                ChangeWaitOrder(&Memory.Wait_order, &Airplane[i].phase, &Airplane[i].Turning);
        }
        ORDER = 0;
    } else {
        for (int i = 0; i < N; ++i) {
            if (Airplane[i].Turning && Airplane[i].phase == 4) {
                ChangeWaitOrder(&Memory.Wait_order, &Airplane[i].phase, &Airplane[i].Turning);
            }
        }
    }
    int area[6];
    for (int i = 0; i < N; ++i) {
        if (!Airplane[i].ARRIVED) {
            dPos = Airplane[i].velocity;
            CheckTerritory(&Airplane[i], &Airplane[0], i, &area[0]);
            RemainingDist = sqrt(pow(Airplane[i].nextPoint->x - Airplane[i].x, 2) +
                                 pow(Airplane[i].nextPoint->y - Airplane[i].y, 2));
            ///*航続距離の更新*///----------------------------------------------------------------------------------------
            Airplane[i].Crusing_Distance += dPos;
            //----------------------------------------------------------------------------------------------------------


            ///*速度の更新*///-------------------------------------------------------------------------------------------
            origin = Airplane[i].velocity;
            if (!Airplane[i].Turning) {
                if (Airplane[i].nextPoint->velocity != 0) {
                    velAcce = (Airplane[i].nextPoint->velocity - Airplane[i].velocity) / RemainingDist;
                } else {
                    RDsub = RemainingDist + sqrt(
                            pow(Airplane[i].nextPoint->next->x - Airplane[i].nextPoint->x, 2)
                            + pow(Airplane[i].nextPoint->next->y - Airplane[i].nextPoint->y, 2)
                    );
                    velAcce = (Airplane[i].nextPoint->next->velocity - Airplane[i].velocity) / RDsub;
                }
                if (velAcce * dPos < VelocityAcceMax) {
                    Airplane[i].velocity += VelocityAcceMax;
                } else {
                    Airplane[i].velocity += velAcce * dPos;
                }
            }
            while (!area[0]) {
                if (area[1] || area[2] || area[3] || area[4]) { Airplane[i].velocity -= toDot(0.001); }
                else if (!(area[1] || area[2] || area[3] || area[4]) && area[5]) { Airplane[i].velocity = origin; }
                if (abs(Airplane[i].velocity - origin) > abs(VelocityAcceMax)) {
                    Airplane[i].velocity += VelocityAcceMax;
                    break;
                }
                CheckTerritory(&Airplane[i], &Airplane[0], i, area);
            }
            //----------------------------------------------------------------------------------------------------------



            ///*角度の更新*///-------------------------------------------------------------------------------------------
            origin = Airplane[i].direction;
            NewDire = atan2(Airplane[i].nextPoint->y - Airplane[i].y, Airplane[i].nextPoint->x - Airplane[i].x);
            if (!Airplane[i].Turning) {
                if (NewDire - origin > 0) {
                    Airplane[i].direction = maxDirection() < NewDire - origin ? Airplane[i].direction += maxDirection()
                                                                              : Airplane[i].direction = NewDire;
                } else if (NewDire - origin < 0) {
                    Airplane[i].direction = -maxDirection() > NewDire - origin ? Airplane[i].direction -= maxDirection()
                                                                               : Airplane[i].direction = NewDire;
                }
            } else {
                if (Airplane[i].phase == 1) {
                    if (abs(Airplane[i].direction - Airplane[i].initialdir) < M_PI) {
                        Airplane[i].direction -= maxDirection();
                    } else {
                        Airplane[i].direction = Airplane[i].initialdir - M_PI;
                        Airplane[i].phase = 2;
                        Airplane[i].initialx = Airplane[i].x;
                        Airplane[i].initialy = Airplane[i].y;
                    }
                } else if (Airplane[i].phase == 3) {
                    if (abs(Airplane[i].direction - Airplane[i].initialdir) < M_PI * 2) {
                        Airplane[i].direction -= maxDirection();
                    } else {
                        Airplane[i].direction = Airplane[i].initialdir;
                        Airplane[i].phase = 4;
                        Airplane[i].initialx = Airplane[i].x;
                        Airplane[i].initialy = Airplane[i].y;
                    }
                }
            }
            int flag1 = 0, flag2 = 0;
            while (!area[0] && !area[5]) {
                if (area[1] || area[4]) {
                    Airplane[i].direction += M_PI / 540.0;
                    flag1 = 1;
                } else if (area[2] || area[3]) {
                    Airplane[i].direction -= M_PI / 540.0;
                    flag2 = 1;
                }
                CheckTerritory(&Airplane[i], &Airplane[0], i, area);
                if (abs(Airplane[i].direction - origin) > maxDirection() || (flag1 && flag2)) {
                    Airplane[i].direction = origin;
                    break;
                }
            }
            //----------------------------------------------------------------------------------------------------------


            ///*高度の更新*///-------------------------------------------------------------------------------------------
            origin = Airplane[i].height;
            if (!Airplane[i].Turning) {
                if (Airplane[i].nextPoint->height != 0) {
                    dropAcce = (Airplane[i].nextPoint->height - Airplane[i].height) / RemainingDist;
                } else {
                    RDsub = RemainingDist + sqrt(
                            pow(Airplane[i].nextPoint->next->x - Airplane[i].nextPoint->x, 2)
                            + pow(Airplane[i].nextPoint->next->y - Airplane[i].nextPoint->y, 2)
                    );
                    dropAcce = (Airplane[i].nextPoint->next->height - Airplane[i].height) / RDsub;
                }
                Airplane[i].height += dropAcce * dPos;
            }
            while (!area[0] && !area[5]) {
                if (area[3] || area[4]) { Airplane[i].height -= (dropAcce * dPos) / 100.0; }
                else if (area[1] || area[2]) { Airplane[i].height += (dropAcce * dPos) / 100.0; }
                if (Airplane[i].height == origin || dropAcce < DropAcceMax) { break; }
                CheckTerritory(&Airplane[i], &Airplane[0], i, area);
            }
            //----------------------------------------------------------------------------------------------------------


            ///*座標の更新*///-------------------------------------------------------------------------------------------
            New_x = Airplane[i].velocity * cos(Airplane[i].direction);
            New_y = Airplane[i].velocity * sin(Airplane[i].direction);
            Airplane[i].x += New_x;
            Airplane[i].y += New_y;
            if (Airplane[i].Turning &&
                sqrt(pow(Airplane[i].initialx - Airplane[i].x, 2) +
                     pow(Airplane[i].initialy - Airplane[i].y, 2)) >= straightDist) {
                if (Airplane[i].phase == 2) {
                    Airplane[i].phase = 3;
                } else if (Airplane[i].phase == 4) {
                    Airplane[i].phase = 1;
                }
            }
            //----------------------------------------------------------------------------------------------------------


            ///*次の目標ポイントの更新*///---------------------------------------------------------------------------------
            if (RemainingDist <= 1) {
                printState(Airplane);
                if (Airplane[i].nextPoint->next == nullptr) {
                    printf("[%d] ARRIVED!\n", i);
                    printState(Airplane);
                    Airplane[i].ARRIVED = 1;
                } else {
                    if (Memory.Wait_order) {
                        Airplane[i].Turning = 1;
                        Airplane[i].initialdir = Airplane[i].direction;
                    } else {
                        if (Airplane[i].phase == 4 || Airplane[i].phase == 0)
                            Airplane[i].nextPoint = Airplane[i].nextPoint->next;
                    }
                }
            }
//            else {
////                if (!Memory.Wait_order && (lastphase[i] == 4 ||
////                                           (lastphase[i] == 1 &&
////                                            abs(Airplane[i].direction - Airplane[i].initialdir) < M_PI / 2))) {
//                if (!Memory.Wait_order && Airplane[i].Turning && Airplane[i].phase == 4) {
//                    Airplane[i].nextPoint = Airplane[i].nextPoint->next;
////                    lastphase[i] = 0;
//                }
//            }
            //----------------------------------------------------------------------------------------------------------
        }
    }

    TimePlus();
}

int main(int argc, char *argv[]) {
    Initialize_Memory();
    Initialize_Point();
    Initialize_Airplane();
    printState(Airplane);
    //opengl----
    glutInit(&argc, argv);          // ライブラリの初期化
    glutInitWindowSize(2048, 1024);  // ウィンドウサイズを指定
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow(argv[0]);      // ウィンドウを作成
    glutReshapeFunc(resize);
    Init();
    glutDisplayFunc(display);       // 表示関数を指定
    glutTimerFunc(1, timer, 0);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();                 // イベント待ち
    //-----------

//    printState(Airplane);

    return 0;
}