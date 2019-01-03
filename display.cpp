//
// Created by Funami on 2019/01/03.
//

#include <GLUT/glut.h>
#include <cmath>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "func.h"
#include "struct.h"
#include "display.h"

extern struct _State Airplane[N];
extern struct _Point ARRON, AWARD, ADDUM, RJTT;
extern struct _Memory Memory;

static const char texture1[] = "map.raw"; /* テクスチャファイル名 */
/*
** 光源
*/


/*
** シーンの描画
*/
static void scene(void) {
    static const GLfloat color[] = {1.0, 1.0, 1.0, 1.0};  /* 材質 (色) */

    /* 材質の設定 */
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

    /* テクスチャマッピング開始 */
    glEnable(GL_TEXTURE_2D);

    /* １枚の４角形を描く */
    glNormal3d(0.0, 0.0, 1.0);
    glBegin(GL_QUADS);
    glTexCoord2d(0.0, 1.0);
    glVertex3d(-100.0, -100.0, 0.0);
    glTexCoord2d(1.0, 1.0);
    glVertex3d(100.0, -100.0, 0.0);
    glTexCoord2d(1.0, 0.0);
    glVertex3d(100.0, 100.0, 0.0);
    glTexCoord2d(0.0, 0.0);
    glVertex3d(-100.0, 100.0, 0.0);
    glEnd();

    /* テクスチャマッピング終了 */
    glDisable(GL_TEXTURE_2D);
}


void display(void) {
    JudgeState();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
/* モデルビュー変換行列の初期化 */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /* シーンの描画 */
    scene();

    /* ダブルバッファリング */
    glutSwapBuffers();
}

void Init() {

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

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) exit(0);//ESCキーで終了
}