//
// Created by Funami on 2019/01/03.
//

#ifndef PROGRAM_DISPLAY_H
#define PROGRAM_DISPLAY_H

#define TEX_WIDTH  2048                      /* テクスチャの幅　　　 */
#define TEX_HEIGHT 1024                      /* テクスチャの高さ　　 */

void Init();

void display(void);

void resize(int w, int h);

void timer(int value);

void reshape(int w, int h);

void keyboard(unsigned char key, int x, int y);

#endif //PROGRAM_DISPLAY_H
