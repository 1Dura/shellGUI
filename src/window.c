#include "../headers/window.h"

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/objects.h"
static void init_ncurses() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);   // включает специальные клавиши (стрелки и т.д)
    nodelay(stdscr, TRUE);  // чтобы getch был неблокирующим
    timeout(3);             // ограничение на частоту опроса ввода, чтобы не лагало
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION,
              NULL);          // включение маски мыши
    printf("\033[?1003h\n");  // включает режим движения мыши
}

int main() {
    init_ncurses();
    int input = -1;
    window main_window;
    int identificators[MAX_OBJECTS_AMOUNT] = {-1};
    BOX boxes[MAX_OBJECTS_AMOUNT] = {0};
    TEXTBOX textboxes[MAX_OBJECTS_AMOUNT] = {0};
    getmaxyx(stdscr, main_window.height, main_window.width);

    boxes[0] = init_box(generate_id(identificators));
    textboxes[0] = init_textbox(generate_id(identificators));
    WINDOW *win = newwin(main_window.height, main_window.width, 0, 0);
    while ((input = getch()) != 27) {
        resize_term(0, 0);
        getmaxyx(stdscr, main_window.height, main_window.width);
        wresize(win, main_window.height, main_window.width);
        werase(win);

        char *text = "%d width | %d height";
        mvwprintw(win, main_window.height - 2, (main_window.width - strlen(text)) / 2, text, main_window.width,
                  main_window.height);

        move_box(&boxes[0], main_window.width / 3, main_window.height / 3);
        draw_box(win, boxes[0]);
        move_box(&textboxes[0].box, main_window.width / 5, main_window.height / 5);
        draw_textbox(win, textboxes[0]);
        char *text1 = "box: id: %d | x: %d | y: %d | width: %d | height: %d";
        mvwprintw(win, main_window.height / 2 + 1, (main_window.width - strlen(text1)) / 2, text1, boxes[0].id,
                  boxes[0].anchor.x, boxes[0].anchor.y, boxes[0].width, boxes[0].height);

        char *text2 = "textbox: id: %d | text: %s";
        mvwprintw(win, main_window.height / 2 + 2, (main_window.width - strlen(text1)) / 2, text2, textboxes[0].box.id,
                  textboxes[0].text);

        box(win, 0, 0);
        wrefresh(win);
        napms(10);
    }

    clear();
    delwin(win);
    endwin();
    return 0;
}
