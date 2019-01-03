//
// Created by Funami on 2019/01/03.
//

#ifndef PROGRAM_DISPLAY_H
#define PROGRAM_DISPLAY_H

#define WIDTH 2880
#define HEIGHT 1800

void Init();

void display(void);

void resize(int w, int h);

void timer(int value);

void keyboard(unsigned char key, int x, int y);

#endif //PROGRAM_DISPLAY_H
