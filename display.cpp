//
// Created by Funami on 2019/01/03.
//

#include <GLUT/glut.h>
#include <GLUT/glpng.h>
#include <cmath>
#include <cstdlib>
#include <stdio.h>
#include "main.h"
#include "func.h"
#include "struct.h"
#include "display.h"

extern struct _State Airplane[N];
extern struct _Point ARRON, AWARD, ADDUM, RJTT;
extern struct _Memory Memory;

pngInfo info;
GLuint texture;

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(0.0, WIDTH, HEIGHT, 0.0, -1.0, 1.0);

    glEnable(GL_TEXTURE_2D);//テクスチャ有効
    glEnable(GL_ALPHA_TEST);//アルファテスト開始
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2d(10, 230);//左下
    glTexCoord2f(0.0f, 0.0f);
    glVertex2d(10, 10);//左上
    glTexCoord2f(1.0f, 0.0f);
    glVertex2d(310, 10);//右上
    glTexCoord2f(1.0f, 1.0f);
    glVertex2d(310, 230);//右下
    glEnd();
    glDisable(GL_ALPHA_TEST);//アルファテスト終了
    glDisable(GL_TEXTURE_2D);//テクスチャ無効

    glutSwapBuffers();
}

void Init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // 消去色指定
    glClear(GL_COLOR_BUFFER_BIT);     // 画面消去
    glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);
    texture = pngBind("objects/map.png", PNG_NOMIPMAP, PNG_ALPHA, &info, GL_CLAMP, GL_NEAREST, GL_NEAREST);
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

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) exit(0);//ESCキーで終了
}