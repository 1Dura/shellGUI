#include "../headers/objects.h"

static int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int generate_id(int *arr) {
    int size = sizeof(&arr) / sizeof(arr[0]);
    qsort(arr, size, sizeof(int), compare);
    int id = 0;
    for (int i = 0; i < size && id == arr[i]; i++) {
        id++;
    }
    return id;
}

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
    box->width = newWidth;
    box->height = newHeight;
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

TEXTBOX init_textbox(int id, char *text) {
    TEXTBOX textbox;
    textbox.box = init_box(id);
    strcpy(textbox.text, DEFAULT_TEXT);
    return textbox;
}

static void draw_text(WINDOW *win, BOX box, char *text) {
    int x = box.anchor.x + 1;
    int y = box.anchor.y + 1;
    int w = box.width - 1;
    int h = box.height - 1;

    int row = 0;
    int column = 0;
    for (int i = y; i < y + h; i++) {
        column = 0;
        for (int j = x; j < x + w; j++) {
            mvwaddch(win, i, j, text[row * w + column]);
            column++;
        }
        row++;
    }
}

void draw_textbox(WINDOW *win, TEXTBOX textbox) {
    draw_box(win, textbox.box);
    draw_text(win, textbox.box, textbox.text);
}
