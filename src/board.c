/*--- INCLUDE ---*/
#include <assert.h>
#include <stdlib.h>
#include "board.h"
#include "board_view.h"
#include "config.h"
#include "tictactoe_errors.h"

#include "log.h"

/*--- VARS AND CONSTS ---*/
static PieceType game_board[MORPION_DIM][MORPION_DIM] = {0};


/*--- FUNCTIONS ---*/

/**
 * Check if the game has to be ended. Only alignment from the last
 * modified square are checked. (this algorythme works for line of 3 pieces)
 *
 * @param [in] boardSquares the board to check. board = [y[x]]
 * @param [in] lastChangeX the colum where the last piece has been put
 * @param [in] lastChangeY the row where the last piece has been put
 * @param [out] gameResult the winning status if the game has ended (value is not set if
 * the game is not finished)
 *
 * @pre lastChangeX must be in [0..2]
 * @pre lastChangeY must be in [0..2]
 * @pre gameResult must point on an allocated GameResult variable
 *
 * @return a boolean that tells if the game is finished
 */
static bool isGameFinished (const PieceType boardSquares[MORPION_DIM][MORPION_DIM], Coordinate lastChangeX, Coordinate lastChangeY, GameResult *gameResult)
{
	// 8 itérations à faire :
	//	- 3 horizontales
	//	- 3 verticales
	//	- 2 diagonales
	//	--> le code est raccourci car le on a le lastChangeX et lastChangeY


	// l'algorythme est concue pour un jeu 3x3
	bool v = (boardSquares[lastChangeY][lastChangeX] == 		// vertical
					boardSquares[(lastChangeY -1)%MORPION_DIM][(lastChangeX)%MORPION_DIM] ==
					boardSquares[(lastChangeY +1)%MORPION_DIM][(lastChangeX)%MORPION_DIM] !=
					NONE
	);

	bool h = (boardSquares[lastChangeY][lastChangeX] == 		// horizontal
					boardSquares[(lastChangeY)%MORPION_DIM][(lastChangeX -1)%MORPION_DIM] ==
					boardSquares[(lastChangeY)%MORPION_DIM][(lastChangeX +1)%MORPION_DIM] !=
					NONE
	);

	bool d = (boardSquares[lastChangeY][lastChangeX] == 	// diagonal
					boardSquares[(lastChangeY -1)%MORPION_DIM][(lastChangeX -1)%MORPION_DIM] ==
					boardSquares[(lastChangeY +1)%MORPION_DIM][(lastChangeX +1)%MORPION_DIM] !=
					NONE
	);

	bool win = v || h || d;

	if(win){
		*gameResult = game_board[lastChangeX][lastChangeY];
	}

	return win;
}


void Board_init (SquareChangeCallback onSquareChange, EndOfGameCallback onEndOfGame)
{
	// init the var
	// game_board = (void *) calloc(MORPION_DIM * MORPION_DIM, sizeof(PieceType));
	for(int y=0; y < MORPION_DIM; y++){
		for(int x=0; x <MORPION_DIM; x++){
			game_board[y][x] = NONE;
		}
	}

	BoardView_init();
	log_m(INFO, "Board initialize");
}


void Board_free ()
{
	// free(game_board);
	BoardView_free();

	log_m(INFO, "BoardView free");
}

PutPieceResult Board_putPiece (Coordinate x, Coordinate y, PieceType kindOfPiece)
{
	// TODO: à compléter
}

PieceType Board_getSquareContent (Coordinate x, Coordinate y)
{
	// TODO: à compléter
}


#if TEST_APP && TEST_board
void TEST_print_board(){
	for(int y=0; y<MORPION_DIM; y++){
		for(int x=0; x<MORPION_DIM; x++){
			switch(game_board[y][x]){
				case NONE:
					printf("|.|");
					break;
				case CROSS:
					printf("|x|");
					break;
				case CIRCLE:
					printf("|o|");
					break;
				default: 
					break;
			}
		}
		printf("\n");
	}
	printf("\n");
}

int main(int argc, char** argv){
	/*--- INIT ---*/
	Board_init(NULL, NULL);


	/*--- CODE ---*/
	TEST_print_board();

	// horizontal wins for cross
	printf("horizontal test\n");
	GameResult result = DRAW;
	game_board[0][0] = CROSS;
	game_board[0][1] = CROSS;
	game_board[0][2] = CROSS;
	TEST_print_board();

	assert(isGameFinished(game_board, 0, 1, &result) == true && result == CROSS_WINS && "Horizontal test");

	// vertical wins for circles
	printf("vetical test\n");
	result = DRAW;
	game_board[0][1] = CIRCLE;
	game_board[1][1] = CIRCLE;
	game_board[2][1] = CIRCLE;
	TEST_print_board();

	assert(isGameFinished(game_board, 0, 1, &result) == true && result == CIRCLE_WINS && "vertical test");

	// diagonal wins for circles
	printf("diagonal test\n");
	result = DRAW;
	game_board[0][2] = CROSS;
	game_board[1][1] = CROSS;
	game_board[2][0] = CROSS;
	TEST_print_board();

	assert(isGameFinished(game_board, 0, 1, &result) == true && result == CROSS_WINS && "diagonal test");


	/*--- END ---*/
	Board_free();
	return EXIT_SUCCESS;
}
#endif