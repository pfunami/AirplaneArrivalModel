//
// Created by Funami on 2019/01/03.
//

#include <GLUT/glut.h>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstdlib>
#include <printf.h>

#include "main.hpp"
#include "func.hpp"
#include "struct.hpp"
#include "display.hpp"

extern struct _State Airplane[N];
extern struct _Point ARRON, AWARD, ADDUM, RJTT;
extern struct _Memory Memory;

static GLubyte image[TEX_HEIGHT][TEX_WIDTH][4];

static int Running = 0;
int ORDER;

double Trance_x(double x) { return x * 1024.0 / 451.9 - 515.0; };

double Trance_y(double y) { return (y - 57.65) * 1024.0 / 285 - 465.0; };

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
    glVertex3d(-512.0, -512.0, 0.0);
    glTexCoord2d(1.0, 1.0);
    glVertex3d(512.0, -512.0, 0.0);
    glTexCoord2d(1.0, 0.0);
    glVertex3d(512.0, 512.0, 0.0);
    glTexCoord2d(0.0, 0.0);
    glVertex3d(-512.0, 512.0, 0.0);
    glEnd();
    /* テクスチャマッピング終了 */
    glDisable(GL_TEXTURE_2D);
}


void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    /* モデルビュー変換行列の初期化 */
    glMatrixMode(GL_PROJECTION);//モード切替え
    glLoadIdentity();
    gluPerspective(-90, -1, 1, 512);  //「透視射影」の設定
    glTranslatef(0.0, 0.0, -512.0);
    /* シーンの描画 */
    scene();
    glPointSize(10);
    glBegin(GL_POINTS);
    glColor4f(0.7, 0.2, 0.2, 0.0);    // 点の色(RGBA)
    glVertex2d(Trance_x(RJTT.x), Trance_y(RJTT.y));
    glVertex2d(Trance_x(ARRON.x), Trance_y(ARRON.y));
    glVertex2d(Trance_x(AWARD.x), Trance_y(AWARD.y));
    glVertex2d(Trance_x(ADDUM.x), Trance_y(ADDUM.y));
    glEnd();
    glColor4f(1.0, 1.0, 1.0, 0.0);    // 点の色(RGBA)
    glBegin(GL_POINTS);
    for (int i = 0; i < N; ++i) {
        glVertex2d(Trance_x(Airplane[i].x), Trance_y(Airplane[i].y));
    }
    glEnd();
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
    if (Running) JudgeState();
    glutPostRedisplay();
    glutTimerFunc(1, timer, 0);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) exit(0);//ESCキーで終了
    if (key == '\x0D') Running = !Running;
    if (key == ' ') ORDER = 1;
}