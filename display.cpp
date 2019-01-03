//
// Created by Funami on 2019/01/03.
//

#include <GLUT/glut.h>
#include <cmath>
#include "main.h"
#include "func.h"
#include "struct.h"
#include "display.h"

extern struct _State Airplane[N];
extern struct _Point ARRON, AWARD, ADDUM, RJTT;
extern struct _Memory Memory;

void display(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // 消去色指定
    glClear(GL_COLOR_BUFFER_BIT);     // 画面消去
}

void resize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0, (double) w / (double) h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(100, timer, 0);
}