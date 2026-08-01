#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <ncurses.h>
#include "../include/ui.h"

void init_ui(void) {
  setlocale(LC_ALL, "");

  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
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

void draw_board(char board[6][6], char *palavra) {
  const int BOARD_Y = (LINES/2) - 2;
  const int BOARD_X = (COLS/2) - 6;

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 5; j++) {
      char ch = board[i][j];

      if (ch == '\0'){
        continue;
      }

      int color;

      if (ch == palavra[j]) {
        color = 2;
      } else if (strchr(palavra, ch) != NULL) {
        color = 4;
      } else {
        color = 3;
      }

      attron(COLOR_PAIR(color));

      if (ch != '\0') {
        mvprintw(
          BOARD_Y + i,
          BOARD_X + j * 3,
          " %c ",
          toupper((unsigned char) ch)
        );
      }

      attroff(COLOR_PAIR(color));
    }
  }
}

void draw_current(char board[6][6], int row) {
  int board_y = (LINES / 2) - 2;
  int board_x = (COLS / 2) - 6;

  for (int col = 0; col < 5; col++) {
    char ch = board[row][col];

    if (ch != '\0') {
      mvprintw(
        board_y + row,
        board_x + col * 3,
        " %c ",
        toupper((unsigned char)ch)
      );

    } else {
      mvprintw(
        board_y + row,
        board_x + col * 3,
        "   "
      );
    }
  }
}
