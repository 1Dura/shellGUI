#ifndef OBJECTS_H_
#define OBJECTS_H_

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT_SIZE 512

int generate_id(int *arr);

/* POINT */
#define DEFAULT_POINT 0
typedef struct {
    unsigned int x;
    unsigned int y;
} POINT;
/* POINT */

/* BOX */
#define DEFAULT_BOX_WIDTH 8
#define DEFAULT_BOX_HEIGHT 5
typedef struct {
    POINT anchor;
    unsigned int width;
    unsigned int height;
    unsigned int id;
} BOX;

BOX init_box(int id);
void move_box(BOX *box, int newX, int newY);
void resize_box(BOX *box, int newWidth, int newHeight);
void draw_box(WINDOW *win, BOX box);
/* BOX */

/* BUTTON */
typedef struct {
    int isPressed;
    BOX box;
} BUTTON;
/* BUTTON */

/* TEXTBOX */
#define DEFAULT_TEXT "yoo bro 1234"
typedef struct {
    char text[MAX_TEXT_SIZE];
    BOX box;
} TEXTBOX;

TEXTBOX init_textbox(int id);
void draw_textbox(WINDOW *win, TEXTBOX textbox);
/* TEXTBOX */

#endif
