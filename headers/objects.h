#ifndef OBJECTS_H_
#define OBJECTS_H_
#include <ncurses.h>
#include <string.h>
#define MAX_TEXT_SIZE 512
#define DEFAULT_MISS_RADIUS 1
/* POINT */
#define DEFAULT_POINT 1
typedef struct {
    int x;
    int y;
} POINT;
/* POINT */

/* ANGLES */
#define LU_ANGLE 2
#define RU_ANGLE 3
#define LD_ANGLE 4
#define RD_ANGLE 5
/* ANGLES */

/* BOX */
#define DEFAULT_BOX_WIDTH 8
#define DEFAULT_BOX_HEIGHT 5
typedef struct {
    POINT anchor;
    int width;
    int height;
    int id;
} BOX;

BOX init_box(int id);
void move_box(BOX *box, int newX, int newY);
void resize_box(BOX *box, int newWidth, int newHeight);
void draw_box(WINDOW *win, BOX box);
int pos_in_box(BOX box, POINT point);
/* BOX */

#endif
