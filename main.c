/*
* Minesweeper game logic
* CS305 HW2 starter
*/

#include "stdio.h"
#include "stdlib.h"

#include "board.h"
#include "cell.h"
#include "minesweep.h"


int main(int argv, char* argc[]){

	// check for number of arguments passed in
	if(argv != 2){
		fprintf(stderr, "USAGE: ./minesweep <board file>. Provide a board file\n");
		return EXIT_FAILURE;
	}
	// call the play game
	play_game(argc[1]);

	return EXIT_SUCCESS;
}