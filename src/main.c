#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>

#include "../include/ui.h"
#include "../include/colors.h"

#define WORD_SIZE 5
#define MAX_ATTEMPTS 6

int main(void) {
  const char palavra[] = "lutar";

  init_ui();
  init_colors();

  int tentativas = MAX_ATTEMPTS;

  bool guessed = false;

  int linha_atual = 0;

  refresh();

  while (tentativas > 0 && !guessed) {
    draw_frame();
    draw_header(tentativas);
    draw_footer();

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
        (LINES/2) - 2 + linha_atual,
        (COLS/2) - 6 + (i * 3),
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

