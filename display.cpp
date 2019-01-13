//
// Created by Funami on 2019/01/03.
//

#include <GLUT/glut.h>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstdlib>
#include <printf.h>
#include <deque>
#include <string>
#include "main.hpp"
#include "func.hpp"
#include "struct.hpp"
#include "display.hpp"

extern struct _State Airplane[N];
extern struct _Point ARRON, AWARD, ADDUM, RJTT;
extern struct _Point STONE, COLOR, CURRY, COUPE, CUTIE, CREAM, CLOAK, CAMEL, CACAO;    //北風・北東からくる便
extern struct _Point BRITZ, BRASS, BACON, BIBLO, BEAST, BONDO, LOC;  //南風・南西からくる便・ADDUMから続く
extern struct _Point DREAD, DENNY, DATUM, DYUKE, BONUS;  //南風・北東からくる便・STONEから続く
struct _Memory Memory;

static GLubyte image[TEX_HEIGHT][TEX_WIDTH][4];
static int Running = 0;
int ORDER, changeable = 1;
extern int TIME[3];
std::deque<double> quex[N];
std::deque<double> quey[N];
std::string t, hv;

int preMousePositionX;
int preMousePositionY;
double viewPointCenterx = 0.0;
double viewPointCentery = 0.0;
double marginx = 1024.0, marginy = 512.0;
bool mouseLeftPressed;
bool mouseRightPressed;
double modelScale = -90;

double Trance_x(double x) { return -x * 2048.0 / 451.9 + 1024.0; };

double Trance_y(double y) { return (y - 57.65) * 1024 / 285 - 465.0; };

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
    glTexCoord2d(1.0, 1.0);
    glVertex3d(1024.0, -512.0, 0.0);
    glTexCoord2d(0.0, 1.0);
    glVertex3d(-1024.0, -512.0, 0.0);
    glTexCoord2d(0.0, 0.0);
    glVertex3d(-1024.0, 512.0, 0.0);
    glTexCoord2d(1.0, 0.0);
    glVertex3d(1024.0, 512.0, 0.0);
    glEnd();
    /* テクスチャマッピング終了 */
    glDisable(GL_TEXTURE_2D);
}

void disp_airplane() {
    glColor3d(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2d(25.0, 0.0);
    glVertex2d(22.0, 6.0);
    glVertex2d(21.5, 14.0);
    glVertex2d(21.5, 85.0);
    glVertex2d(25, 91);
    glVertex2d(28.5, 85.0);
    glVertex2d(28.5, 14.0);
    glVertex2d(28.0, 6.0);
    glVertex2d(25.0, 0.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2d(21.5, 30.0);
    glVertex2d(3.0, 67.0);
    glVertex2d(4.0, 70.0);
    glVertex2d(21.5, 55.0);
    glVertex2d(21.5, 30.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2d(21.5, 85.0);
    glVertex2d(14, 100);
    glVertex2d(25, 91);
    glVertex2d(21.5, 85.0);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(25, 91);
    glVertex2d(38.5, 100);
    glVertex2d(28.5, 85.0);
    glVertex2d(25, 91);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2d(28.5, 55.0);
    glVertex2d(46.0, 70.0);
    glVertex2d(47.0, 67.0);
    glVertex2d(28.5, 30.0);
    glVertex2d(28.5, 55.0);
    glEnd();
}

void DrawString(std::string str, double x0, double y0) {
    // 平行投影にする
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // 画面上にテキスト描画
    glRasterPos2d(x0, y0);
    int size = (int) str.size();
    for (int i = 0; i < size; ++i) {
        char ic = str[i];
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ic);
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void DispPoint() {
    glPointSize(10);
    glColor4f(1.0, 0.0, 0.0, 0.0);    // 点の色(RGBA)
    glBegin(GL_POINTS);
    glVertex2d(RJTT.x, RJTT.y);
    glEnd();

    glColor4f(0.0, 0.7, 0.7, 0.0);    // 点の色(RGBA)
    glPointSize(5);
    glBegin(GL_POINTS);
    if (!Memory.Wind_direction) {
        glVertex2d(BONDO.x, BONDO.y);
        glVertex2d(LOC.x, LOC.y);
    }
    struct _Point *point;
    point = &ADDUM;
    glColor4f(0.2, 0.7, 0.2, 0.0);    // 点の色(RGBA)
    do {
        glVertex2d(point->x, point->y);
        point = point->next;
    } while (point != &RJTT && point != &BONDO);

    glColor4f(0.7, 0.7, 0.2, 0.0);    // 点の色(RGBA)
    point = &STONE;
    do {
        glVertex2d(point->x, point->y);
        point = point->next;
    } while (point != &RJTT && point != &BONDO);
    glEnd();
}

void display(void) {
    Change_Branch();
    //deque
    for (int i = 0; i < N; ++i) {
        quex[i].push_front(Airplane[i].x);
        quey[i].push_front(Airplane[i].y);
        if (quex[i].size() > QUEUE_SIZE) { quex[i].pop_back(); }
        if (quey[i].size() > QUEUE_SIZE) { quey[i].pop_back(); }
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    /* モデルビュー変換行列の初期化 */
    glMatrixMode(GL_PROJECTION);//モード切替え
    glLoadIdentity();
    gluPerspective(modelScale, -1024.0 / 512.0, 1, 1000);  //「透視射影」の設定
    gluLookAt(viewPointCenterx, viewPointCentery, 0.0, viewPointCenterx, viewPointCentery, -500.0, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.0, -512);
    /* シーンの描画 */
    scene();
    DispPoint();
    glColor4f(1.0, 1.0, 1.0, 0.0);    // 点の色(RGBA)
    glPushMatrix();
    for (int i = 0; i < N; ++i) {
        glPushMatrix();
        glTranslated(Airplane[i].x, Airplane[i].y, 0.0);
        glRotated(90.0 + toFreq(Airplane[i].direction), 0, 0, 1);
        glScaled(0.6, 0.3, 0);
        glTranslated(-25.0, -50.0, 0.0);
        disp_airplane();
        glPopMatrix();
    }
    glPopMatrix();
    glLineWidth(1.0);
    for (int k = 0; k < N; ++k) {
        glBegin(GL_LINE_STRIP);
        for (int j = 0; j < quex[k].size(); ++j) {
            glVertex2d(quex[k].front(), quey[k].front());
            quex[k].push_back(quex[k].front());
            quex[k].pop_front();
            quey[k].push_back(quey[k].front());
            quey[k].pop_front();
        }
        glEnd();
    }


    if (Memory.Wind_direction == 1) { DrawString("WIND : NORTH", -0.98, 0.95); }
    else { DrawString("WIND : SOUTH", -0.98, 0.95); }
    if (Memory.Wait_order == 1) { DrawString("HOLD : ON", -0.98, 0.9); }
    else { DrawString("HOLD : OFF", -0.98, 0.9); }
    t = "";
    for (int l = 2; l >= 0; --l) {
        if (TIME[l] < 10) {
            t += "0" + std::to_string(TIME[l]);
        } else {
            t += std::to_string(TIME[l]);
        }
        if (l != 0) { t += ":"; }
    }
    DrawString(t, -0.98, 0.85);
    for (int m = 0; m < N; ++m) {
        hv = std::to_string(Airplane[m].height);
        for (int i = 0; i < 4; ++i) { hv.pop_back(); }
        hv += "[m]";
        DrawString(hv, (-Airplane[m].x + viewPointCenterx) / 1024.0 / tan(toRad(modelScale / 2.0)) + 0.015,
                   (Airplane[m].y - viewPointCentery) / 512.0 / tan(toRad(modelScale / 2.0)) + 0.0075);
        hv = std::to_string(toKm(Airplane[m].velocity));
        for (int i = 0; i < 4; ++i) { hv.pop_back(); }
        hv += "[km/h]";
        DrawString(hv, (-Airplane[m].x + viewPointCenterx) / 1024.0 / tan(toRad(modelScale / 2.0)) + 0.015,
                   (Airplane[m].y - viewPointCentery) / 512.0 / tan(toRad(modelScale / 2.0)) + 0.05);
    }

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
}

void resize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(-90.0, (double) w / (double) h, 1.0, 512.0);
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

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) exit(0);//ESCキーで終了
    if (key == '\x0D') {
        Running = !Running;
        changeable = 0;
    }
    if (key == ' ') ORDER = 1;
    if (changeable) {
        if (key == 'n') Memory.Wind_direction = 1;  //北風
        if (key == 's') Memory.Wind_direction = 0;  //南風
    }
}

void mouse(int button, int state, int x, int y) {
    mouseLeftPressed = mouseRightPressed = false;

    switch (button) {
        case GLUT_LEFT_BUTTON:
            preMousePositionX = x;
            preMousePositionY = y;
            mouseLeftPressed = true;
            break;
        case GLUT_MIDDLE_BUTTON:
            break;
        case GLUT_RIGHT_BUTTON:
            preMousePositionX = x;
            preMousePositionY = y;
            mouseRightPressed = true;
            break;
        default:
            break;
    }
}


void motion(int x, int y) {
    int diffX = x - preMousePositionX;
    int diffY = y - preMousePositionY;
    marginx = modelScale / -90 * 1024;
    marginy = modelScale / -90 * 512;

    if (mouseLeftPressed) {
        if (viewPointCenterx - diffX + marginx < 1024 && viewPointCenterx - diffX - marginx > -1024) {
            viewPointCenterx -= diffX;
        }
        if (viewPointCentery - diffY + marginy < 512 && viewPointCentery - diffY - marginy > -512) {
            viewPointCentery -= diffY;
        }
    } else if (mouseRightPressed) {
        double scale = 1.0 + diffY * 0.01;
        if (modelScale * scale < -15 && modelScale * scale >= -90) {
            modelScale *= scale;
        }
    }
    preMousePositionX = x;
    preMousePositionY = y;
    glutPostRedisplay();
}

void timer(int value) {
    if (Running) JudgeState();
    glutPostRedisplay();
    glutTimerFunc(10, timer, 0);
}

int OpenGL_main(int argc, char *argv[]) {
    glutInit(&argc, argv);          // ライブラリの初期化
    glutInitWindowSize(2048, 1024);  // ウィンドウサイズを指定
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow(argv[0]);      // ウィンドウを作成
    glutReshapeFunc(resize);
    glutFullScreen();
    Init();
    glutDisplayFunc(display);       // 表示関数を指定
    glutTimerFunc(10, timer, 0);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutMainLoop();                 // イベント待ち
}