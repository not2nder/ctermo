#ifndef UI_H
#define UI_H

void init_ui(void);
void exit_ui(void);
void draw_header(int tentativas);
void draw_footer(void);
void draw_frame(void);
void draw_board(char board[6][6], char *palavra);
void draw_current(char board[6][6], int row);

#endif
