//
// Created by Funami on 2019/01/03.
//

#ifndef PROGRAM_DISPLAY_H
#define PROGRAM_DISPLAY_H

#define TEXWIDTH  256                      /* テクスチャの幅　　　 */
#define TEXHEIGHT 256                      /* テクスチャの高さ　　 */

void Init();

void display(void);

void resize(int w, int h);

void timer(int value);

void keyboard(unsigned char key, int x, int y);

#endif //PROGRAM_DISPLAY_H
