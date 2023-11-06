// #include all necessary .h files here.
//#include "minesweeper.h"
#include "board.h"
#include "cell.h"

int check_mine(game*, int, int);




/* print_game 
* args: pointer to the current board struct
* out: void
* prints the game board: 
    if cell color is white and number of mines is >0, print mine count otherwise
    if cell is white, print the mine count 0 otherwise
    if cell color is black 'B', print B otherwise, 
    if cell color is gray 'E'
*/
void print_board(game* board){
    printf("Board colors %d x %d\n", board->row_max, board->col_max);
    for(int i=0; i< board->row_max; i++){
        for(int j=0; j < board->col_max; j++){
            if(board->cells[i][j].color == white && board->cells[i][j].mine >0)
                printf("%d\t", board->cells[i][j].mine);
            else if (board->cells[i][j].color == white)
                printf("0\t");
            else if (board->cells[i][j].color == black)
                printf("B\t");
            else 
                printf("E\t");
        }
        printf("\n");
    }
    // uncommnet this to print the board again showing the mine locations
    // printf("Mines on the Board (-1: mine, 1: otherwise): %d x %d\n", board->row_max, board->col_max);
    // for(int i=0; i< board->row_max; i++){
    //     for(int j=0; j < board->col_max; j++){
    //         printf("%d\t", board->cells[i][j].mine);
    //     }
    //     printf("\n");
    // }
}

game* load_board(char* board) {
  game* curr;
  curr = malloc(sizeof(game));

  FILE* boardFile = fopen(board, "r");
  if(boardFile == NULL) {
    printf("file could not be opened");
    return NULL;
  }
  fscanf(boardFile, "%d %d", &curr->row_max, &curr->col_max);

  if(curr->row_max < 3 || curr->col_max < 3) return NULL;

   char c;
   int x = 0;
   int lines;
   int total;
   for(c = getc(boardFile); c != EOF; c = getc(boardFile)) {
     if(c == '\n'){
       lines++;
       if(x % curr->col_max != 0 && lines > 1) return NULL;
       x = 0;
     }
     if(c >= '0' && c <= '9' && lines > 0) {
       total++;
       x++;
     }
   }
   if(total != curr->col_max * curr->row_max) return NULL;
   rewind(boardFile);
   fscanf(boardFile, "%d %d", &curr->row_max, &curr->col_max);

  int i, j;
  curr->cells = malloc(sizeof(cell*) * curr->row_max);
  for(i = 0;i < curr->row_max; i++) {
    curr->cells[i] = malloc(sizeof(cell) * curr->col_max);
  }//mallocs every cell in the 2D cell array

   for(i = 0;i < curr->row_max; i++) {
     for(j = 0; j < curr->col_max; j++) {
       curr->cells[i][j].color = gray;
       fscanf(boardFile, "%d", &curr->cells[i][j].mine);
     }
   }//assigns gray to every cell and assings mine value

   for(i = 0; i < curr->row_max; i++) {
     for(j = 0; j < curr->col_max; j++) {
       if(curr->cells[i][j].mine != -1) {
	 if(curr->cells[i][j].mine < -1) return NULL;
	 int x = 0;
	 x += check_mine(curr, i+1, j-1);
	 x += check_mine(curr, i+1, j+1);
	 x += check_mine(curr, i+1, j);
	 x += check_mine(curr, i, j+1);
	 x += check_mine(curr, i, j-1);
	 x += check_mine(curr, i-1, j+1);
	 x += check_mine(curr, i-1, j);
	 x += check_mine(curr, i-1, j-1);

	 if(x != curr->cells[i][j].mine) return NULL;
       }
     }
   }

 
  fclose(boardFile); 
  return curr;
}

int check_mine(game* curr, int row, int col) {
  if(row < 0 || col < 0 || row > curr->row_max-1 || col > curr->col_max-1)
    return 0;
  if(curr->cells[row][col].mine < 0) return 1;
  return 0;
}
