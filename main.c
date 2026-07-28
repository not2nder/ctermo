#include <ctype.h>
#include <ncurses.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char *argv[]) {
  const char palavra[] = "lutar";

  initscr();
  noecho();
  curs_set(0);
  box(stdscr, 0, 0);

  int h, w;
  getmaxyx(stdscr, h, w);

  start_color();

  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_WHITE, COLOR_GREEN);
  init_pair(3, COLOR_WHITE, COLOR_RED);
  init_pair(4, COLOR_WHITE, COLOR_YELLOW);
  
  int tentativas = 5;

  bool guessed = false;

  int linha_atual = 0;

  while (tentativas > 0 && !guessed) {
    mvprintw(0, (w/2) - 7, "TENTATIVAS: %d", tentativas);

    char tentativa[6];

    for (int i = 0; i < 5; i++) {
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

      refresh();
    }

    tentativa[5] = '\0';
    
    if (strcmp(tentativa, palavra) == 0) {
      guessed = true;
    }

    tentativas--;
    linha_atual++;
  }

  getch();

  endwin();
  return 0;
}

