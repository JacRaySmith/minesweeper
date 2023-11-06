#include "stdio.h"
#include "stdlib.h"

// #include all necessary .h files here
#include "minesweep.h"
#include "board.h"
#include "cell.h"
/* play_game
* args: f_name -- unchecked file name that contains board cofiguration
* out: int return game status if needed for the best score keeping
* creates the game instance
*  reads command line for click's x/y and click type (forever unless otherwise specified):
*  Enter row in range 1-board height: enter column range 1-board width click type(0: unvover 1: mine)
*  Example= 1:3 0 -- row=1 col=3 try uncover
*  Example= 2:1 1 -- row=2 col=1 mark as a mine
*  Enter '-1' to check if game is won and quit the game
*
*  call process_click with x/y and a move type
*  check the process_click return for the game result 
*/

int play_game(char* f_name){
    game* board = load_board(f_name);
    if(board == NULL){
        fprintf(stderr, "ERROR: Cound not allocate board or read from file");
        return EXIT_FAILURE;
    }
    int ret, r, c, m = 0;
    while(1){
        print_board(board);
        printf("Enter row(1-%d):column(1-%d) and click type(0: unvover 1: mark a mine)\n", board->row_max, board->col_max);
        printf("Example= 1:3 0 -- row=1 col=3 try uncover\n");
        printf("Example= 2:1 1 -- row=2 col=1 mark as a mine\n");
        printf("Enter '-1' to quit the game \n");

        scanf("%d:%d%d", &r, &c, &m);
        if(r==-1 || c==-1 || m==-1){
            if(check_game(board))
                printf("CONGRATS YOU WON!!!\n");    
            else
                printf("YOU LOST -- GAME OVER -- mines mis-identified\n");    
            break;
        }else if(r<1 || c<1 || r > board->row_max || c > board->col_max || m < 0 || m > 1)
            printf("Illegal move or click type, try again!\n");
        else{
            ret = process_click(board, --r, --c, m);
            if (ret == 0){
                printf("GAME OVER, you stepped on a mine or marked it as a mine\n");
                break;
            }else
                printf("Good one, keep on clicking\n");
        }

    }
    printf("Thank you for playing\n");
    free_board(board);
    return EXIT_SUCCESS;
}

int process_click(game* BOARD, int row, int col, int inp) {
  if(inp == 1) {
    if(BOARD->cells[row][col].color == gray) {
      BOARD->cells[row][col].color = black;
    }
    else if(BOARD->cells[row][col].color == black) {
       BOARD->cells[row][col].color = gray;
    }
    return 1;
  }//flagging the spot

  if(BOARD->cells[row][col].color == black || BOARD->cells[row][col].color == white) {
    return 1;
  }
  
  if(BOARD->cells[row][col].color == gray) {
    if(BOARD->cells[row][col].mine > 0) BOARD->cells[row][col].color = white;
    if(BOARD->cells[row][col].mine == -1) return 0;
  }

  if(check_game(BOARD) == 1) return 0;
  return uncover(BOARD, row, col);
  return 1;
}

int check_game(game* BOARD) {
  int i, j;
  for(i = 0; i < BOARD->row_max; i++) {
    for(j = 0; j < BOARD->col_max; j++) {
      if((BOARD->cells[i][j].color != black && BOARD->cells[i][j].mine ==-1) ||
	 (BOARD->cells[i][j].color == black && BOARD->cells[i][j].mine != -1)) {
	return 0;
      }
    }
  }
  return 1;
}

int uncover(game* BOARD, int row, int col) {
  if(row < 0 || col < 0 || row > BOARD->row_max-1 || col > BOARD->col_max-1) return 1;
  //printf("11111111111");
  if(BOARD->cells[row][col].color != gray) return 1;
  //printf("22222222222");
  BOARD->cells[row][col].color = white;
  if(BOARD->cells[row][col].mine > 0) return 1;
  //printf("33333333333");
  
 
  //printf("HHEEEYEYYEYYEYYEE");
  uncover(BOARD, row + 1, col + 1);
  uncover(BOARD, row + 1, col - 1);
  uncover(BOARD, row + 1, col);
  uncover(BOARD, row - 1, col + 1);
  uncover(BOARD, row - 1, col - 1);
  uncover(BOARD, row - 1, col);
  uncover(BOARD, row, col + 1);
  uncover(BOARD, row, col - 1);
  return 1;
}

void free_board(game* BOARD) {
  
}
