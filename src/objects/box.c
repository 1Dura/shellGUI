#include "../../headers/objects.h"

BOX init_box(int id) {
    BOX box;
    box.anchor.x = DEFAULT_POINT;
    box.anchor.y = DEFAULT_POINT;
    box.height = DEFAULT_BOX_HEIGHT;
    box.width = DEFAULT_BOX_WIDTH;
    box.id = id;
    return box;
}

void move_box(BOX *box, int newX, int newY) {
    box->anchor.x = newX;
    box->anchor.y = newY;
}

void resize_box(BOX *box, int newWidth, int newHeight) {
    if (newHeight > 0 && newWidth > 0) {
        box->width = newWidth;
        box->height = newHeight;
    }
}

void draw_box(WINDOW *win, BOX box) {
    int x = box.anchor.x;
    int y = box.anchor.y;
    int width = box.width;
    int height = box.height;
    for (int i = x; i < x + width; i++) {
        mvwprintw(win, y, i, "-");
        mvwprintw(win, y + height, i, "-");
    }
    for (int i = y; i < y + height; i++) {
        mvwprintw(win, i, x, "|");
        mvwprintw(win, i, x + width, "|");
    }
    mvwprintw(win, y, x, "+");
    mvwprintw(win, y + height, x, "+");
    mvwprintw(win, y, x + width, "+");
    mvwprintw(win, y + height, x + width, "+");
}
int pos_in_sphere(POINT center, POINT check, int radius) {
    if (check.x >= center.x - radius && check.x <= center.x + radius &&
        check.y <= center.y + radius && check.y >= center.y - radius) {
        return 1;
    }
    return 0;
}

int pos_in_box(BOX box, POINT point) {
    int x = point.x;
    int y = point.y;
    int result = 1;
    POINT RD = {box.anchor.x + box.width, box.anchor.y + box.height};
    if (pos_in_sphere(box.anchor, point, DEFAULT_MISS_RADIUS)) {
        result = LU_ANGLE;
    } else if (x == box.anchor.x + box.width && y == box.anchor.y) {
        result = RU_ANGLE;
    } else if (x == box.anchor.x && y == box.anchor.y + box.height) {
        result = LD_ANGLE;
    } else if (pos_in_sphere(RD, point, DEFAULT_MISS_RADIUS)) {
        result = RD_ANGLE;
    } else if (x < box.anchor.x || y < box.anchor.y ||
               x > box.anchor.x + box.width || y > box.anchor.y + box.height) {
        result = 0;
    }
    return result;
}
