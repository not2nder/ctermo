#include <locale.h>
#include <ncurses.h>
#include "../include/ui.h"

void init_ui(void) {
  setlocale(LC_ALL, "");

  initscr();
  noecho();
  curs_set(0);
}

void exit_ui(void) {
  endwin();
}

void draw_header(int tentativas) {
  mvprintw(1, 2, "TERMO");
  mvprintw(1, COLS - 15, "TENTATIVAS: %d", tentativas);
  mvaddch(2, 0, ACS_LTEE);
  mvhline(2, 1, ACS_HLINE, COLS - 2);
  mvaddch(2, COLS - 1, ACS_RTEE);
}

void draw_footer(void) {
  mvhline(LINES - 3, 1, ACS_HLINE, COLS - 2);
  mvaddch(LINES - 3, 0, ACS_LTEE);

  attron(A_REVERSE);
  attron(COLOR_PAIR(2));
  mvprintw(LINES - 2, 2, "■");
  attroff(COLOR_PAIR(2));
  attroff(A_REVERSE);
  printw(" Certa ");

  attron(A_REVERSE);
  attron(COLOR_PAIR(3));
  printw("■");
  attroff(COLOR_PAIR(3));
  attroff(A_REVERSE);
  printw(" Errada ");

  attron(A_REVERSE);
  attron(COLOR_PAIR(4));
  printw("■");
  attroff(COLOR_PAIR(4));
  attroff(A_REVERSE);
  printw(" Posição errada");
  
  mvaddch(LINES - 3, COLS - 1, ACS_RTEE);
}

void draw_frame(void) {
  box(stdscr, 0, 0);
}
