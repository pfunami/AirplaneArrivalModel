//
// Created by Funami on 2019/01/03.
//

#include <GLUT/glut.h>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstdlib>
#include "main.h"
#include "func.h"
#include "struct.h"
#include "display.h"

extern struct _State Airplane[N];
extern struct _Point ARRON, AWARD, ADDUM, RJTT;
extern struct _Memory Memory;

static GLubyte image[TEX_HEIGHT][TEX_WIDTH][4];


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
    glMatrixMode(GL_PROJECTION);//モード切替え
    glLoadIdentity();
    gluPerspective(-90, -1, 1, 500);  //「透視射影」の設定
    glTranslatef(0.0, 0.0, -100.0);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-5.0, -5.0, 0.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-5.0, 5.0, 0.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(5.0, 5.0, 0.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(5.0, -5.0, 0.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    /* シーンの描画 */
    scene();

    /* ダブルバッファリング */
    glutSwapBuffers();
}

void Init() {
    FILE *fp;
    int x, y;

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);

    /* texture file open */
    if ((fp = fopen("map.tga", "rb")) == NULL) {
        fprintf(stderr, "texture file cannot open\n");
        return;
    }
    fseek(fp, 18, SEEK_SET);
    for (x = 0; x < TEX_HEIGHT; x++) {
        for (y = 0; y < TEX_WIDTH; y++) {
            image[x][y][2] = fgetc(fp);/* B */
            image[x][y][1] = fgetc(fp);/* G */
            image[x][y][0] = fgetc(fp);/* R */
            image[x][y][3] = fgetc(fp);/* alpha */
        }
    }
    fclose(fp);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEX_WIDTH, TEX_HEIGHT,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

//    glClearColor(1.0, 1.0, 1.0, 1.0);  // 消去色指定
//    glClear(GL_COLOR_BUFFER_BIT);     // 画面消去
}

void resize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0, (double) w / (double) h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(100, timer, 0);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) exit(0);//ESCキーで終了
}