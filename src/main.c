#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>

#include "../include/ui.h"
#include "../include/colors.h"

#define WORD_SIZE 5
#define MAX_ATTEMPTS 6

int main(void) {
  char *palavra = "lutar";
  char board[MAX_ATTEMPTS][WORD_SIZE + 1] = {0};
  bool guessed = false;

  init_ui();
  init_colors();

  int tentativas = MAX_ATTEMPTS;

  int linha_atual = 0;
  int caractere_atual = 0;

  refresh();

  while (tentativas > 0 && !guessed) {
    draw_frame();
    draw_header(tentativas);
    draw_footer();
    draw_board(board, palavra);
    draw_current(board, linha_atual);

    int ch = getch();

    if (ch == KEY_RESIZE) {
      clear();
      continue;
    }

    if (ch == KEY_BACKSPACE) {
      if (caractere_atual > 0) {
        caractere_atual--;
        board[linha_atual][caractere_atual] = 0;
        clear();
      }
      continue;
    }

    if (ch == '\n') {
      if (caractere_atual != WORD_SIZE) {
        continue;
      }

      char tentativa[WORD_SIZE + 1];

      memcpy(tentativa, board[linha_atual], WORD_SIZE);

      tentativa[WORD_SIZE] = '\0';
 
      if (strcmp(tentativa, palavra) == 0) {
        guessed = true;
      }

      linha_atual++;
      caractere_atual = 0;
      tentativas--;

      draw_board(board, palavra);
      continue;
    }
        
    if (caractere_atual < WORD_SIZE && isalpha(ch)) {
      board[linha_atual][caractere_atual] = ch;
      caractere_atual++;
    }    
  }

  getch();
  exit_ui();
  
  return 0;
}

