#include "../../headers/objects.h"

TEXTBOX init_textbox(int id, char *text) {
    TEXTBOX textbox;
    textbox.box = init_box(id);
    if (text == NULL) {
        text = DEFAULT_TEXT;
    }
    strcpy(textbox.text, text);
    return textbox;
}

static void draw_text(WINDOW *win, BOX box, char *text) {
    int x = box.anchor.x + 1;
    int y = box.anchor.y + 1;
    int w = box.width - 1;
    int h = box.height - 1;

    int row = 0;
    int column = 0;

    int flag = 0;
    for (int i = y; !flag && i < y + h; i++) {
        column = 0;
        for (int j = x; !flag && j < x + w; j++) {
            char c = text[row * w + column];
            if (c == '\0') {
                flag = 1;
            } else {
                mvwaddch(win, i, j, c);
                column++;
            }
        }
        row++;
    }
}

void draw_textbox(WINDOW *win, TEXTBOX textbox) {
    draw_box(win, textbox.box);
    draw_text(win, textbox.box, textbox.text);
}

void set_text_for_textbox(TEXTBOX *textbox, char *newtext) {
    if (newtext == NULL) {
        strcpy(textbox->text, "NULL");
    } else {
        strcpy(textbox->text, newtext);
    }
}
