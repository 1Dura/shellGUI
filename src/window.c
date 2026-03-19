#include "../headers/window.h"

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>

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
    int input;
    window main_window;
    getmaxyx(stdscr, main_window.height, main_window.width);
    WINDOW *win = newwin(main_window.height, main_window.width, 0, 0);
    bool need_redraw = true;
    int last_h = main_window.height;
    int last_w = main_window.width;
    while ((input = getch()) != 27) {
        resize_term(0, 0);
        getmaxyx(stdscr, main_window.height, main_window.width);
        if (main_window.height != last_h || main_window.width != last_w || input == KEY_F(11) || input == KEY_RESIZE) {
            need_redraw = true;
        }

        if (need_redraw) {
            wresize(win, main_window.height, main_window.width);
            last_h = main_window.height;
            last_w = main_window.width;
            werase(win);

            mvwprintw(win, 3, 3, "Now its %d rows and %d columns", main_window.height, main_window.width);
            box(win, 0, 0);
            wrefresh(win);
            need_redraw = false;
        }
    }
    clear();
    delwin(win);
    endwin();
    return 0;
}
