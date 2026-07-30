#include <ctype.h>
#include <locale.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#define WORD_SIZE 5
#define MAX_ATTEMPTS 6

void init_ui() {
  setlocale(LC_ALL, "");
  initscr();
  noecho();
  curs_set(0);
}

void init_colors() {
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_BLACK, COLOR_GREEN);
  init_pair(3, COLOR_BLACK, COLOR_RED);
  init_pair(4, COLOR_BLACK, COLOR_YELLOW);
}

void exit_ui() {
  endwin();
}

void draw_header(int width, int tentativas) {
  mvprintw(0, (width/2) - 6, "TENTATIVAS %d", tentativas);
}

void draw_footer() {
  attron(COLOR_PAIR(2));
  mvprintw(LINES - 2, 1, " ");
  attroff(COLOR_PAIR(2));
  printw(" Certa ");
  
  attron(COLOR_PAIR(3));
  printw(" ");
  attroff(COLOR_PAIR(3));
  printw(" Errada ");

  attron(COLOR_PAIR(4));
  printw(" ");
  attroff(COLOR_PAIR(4));
  printw(" Posição errada");
}

int main(int argc, char *argv[]) {
  const char palavra[] = "lutar";

  init_ui();
  init_colors();

  box(stdscr, 0, 0);

  int h, w;
  getmaxyx(stdscr, h, w);
  
  int tentativas = MAX_ATTEMPTS;

  bool guessed = false;

  int linha_atual = 0;

  draw_footer();
  refresh();

  while (tentativas > 0 && !guessed) {
    draw_header(w, tentativas);
    char tentativa[WORD_SIZE + 1];

    for (int i = 0; i < WORD_SIZE; i++) {
      char ch = getch();
      tentativa[i] = ch;

      if (ch == palavra[i]) {
        attron(COLOR_PAIR(2));
      }
      else if (strchr(palavra, ch) != NULL) {
        attron(COLOR_PAIR(4));
      }
      else {
        attron(COLOR_PAIR(3));
      }

      mvprintw(
        (h/2) - 2 + linha_atual,
        (w/2) - 6 + (i * 3),
        " %c ",
        toupper(ch)
      );

      attroff(COLOR_PAIR(2));
      attroff(COLOR_PAIR(3));
      attroff(COLOR_PAIR(4));

      refresh();
    }

    tentativa[WORD_SIZE] = '\0';
    
    if (strcmp(tentativa, palavra) == 0) {
      guessed = true;
    }

    tentativas--;
    linha_atual++;
  }

  getch();
  exit_ui();
  
  return 0;
}

