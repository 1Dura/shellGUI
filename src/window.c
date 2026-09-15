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
    keypad(stdscr, TRUE);    // включает специальные клавиши (стрелки и т.д) и
                             // регистрирует нажатия мыши правильно
    nodelay(stdscr, FALSE);  // чтобы getch был неблокирующим
    timeout(16);  // ограничение на частоту опроса ввода, чтобы не лагало
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION,
              NULL);  // включение маски мыши (наблюдаем за всеми ивентами мыши)
    printf("\033[?1003h\n");  // включает режим движения мыши
    mouseinterval(50);        // время ожидания для подтверждения двойного клика
}

static void show_info(WINDOW *win, window main_window, int cx, int cy,
                      int pressed) {
    char *text = "%d width | %d height | x: %d y: %d | pressed: %d";
    mvwprintw(win, main_window.height - 2,
              (main_window.width - strlen(text)) / 2, text, main_window.width,
              main_window.height, cx, cy, pressed);
}

static int button1_down(mmask_t bstate) {
    // явное нажатие
    if (bstate & (BUTTON1_PRESSED | BUTTON1_CLICKED | BUTTON1_DOUBLE_CLICKED |
                  BUTTON1_TRIPLE_CLICKED)) {
        return 1;
    }

    // явное отпускание
    if (bstate & BUTTON1_RELEASED) {
        return 0;
    }

    return -1;  // «не знаю» — состояние не изменилось
}

int main() {
    init_ncurses();
    int input = -1;
    window main_window;
    getmaxyx(stdscr, main_window.height, main_window.width);

    WINDOW *win = newwin(main_window.height, main_window.width, 0, 0);
    nodelay(win, TRUE);
    MEVENT event;
    int pressed = -1;
    // POINT cursor;  // необходимо для сохранения данных о позиции курсора,
    // иначе
    //                // event.x/y слетает на ноль

    while ((input = wgetch(stdscr)) != 27) {
        if (input == KEY_MOUSE) {
            getmouse(&event);
            int flag = button1_down(event.bstate);
            if (flag != -1) {
                pressed = flag;
            }
        }

        // if (event.bstate & BUTTON1_PRESSED) {
        //     pressed = 1;
        // }
        // if (event.bstate & BUTTON1_RELEASED) {
        //     pressed = 0;
        // }

        resize_term(0, 0);
        getmaxyx(stdscr, main_window.height, main_window.width);
        wresize(win, main_window.height, main_window.width);
        werase(win);
        // show_info(win, main_window, cursor.x, cursor.y, pressed);
        show_info(win, main_window, event.x, event.y, pressed);

        box(win, 0, 0);
        wrefresh(win);

        // napms(1);
    }

    clear();
    delwin(win);
    endwin();
    return 0;
}
