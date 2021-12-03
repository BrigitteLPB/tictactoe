/*--- INCLUDE ---*/
#include <stdlib.h>
#include "board.h"
#include "board_view.h"
#include "config.h"
#include "tictactoe_errors.h"
#include "assert_m.h"

#include "log.h"

/*--- VARS AND CONSTS ---*/
static PieceType game_board[MORPION_DIM][MORPION_DIM] = {0};
static SquareChangeCallback onSquareChange_cb = NULL;
static EndOfGameCallback onEndOfGame_cb = NULL;

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
	// init the board
	for(int y=0; y < MORPION_DIM; y++){
		for(int x=0; x <MORPION_DIM; x++){
			game_board[y][x] = NONE;
		}
	}

	onSquareChange_cb = onSquareChange;
	onEndOfGame_cb = onEndOfGame;

	BoardView_init();
	log_m(INFO, "Board initialize");
}


void Board_free ()
{
	BoardView_free();

	log_m(INFO, "Board free");
}

PutPieceResult Board_putPiece (Coordinate x, Coordinate y, PieceType kindOfPiece)
{
	// check bounds
	if(x >= 0 && x < MORPION_DIM && y >=0 && y < MORPION_DIM){
		if(kindOfPiece != NONE){
			if(game_board[y][x] == NONE){
				game_board[y][x] = kindOfPiece;
				
				// calling the on change callbacks
				if(onSquareChange_cb != NULL){
					onSquareChange_cb(x, y, kindOfPiece);	
				}

				return PIECE_IN_PLACE;
			}else{
				return SQUARE_IS_NOT_EMPTY;
			}
		}else{
			return SQUARE_IS_NOT_EMPTY;
		}
	}else{
		fatalError((const char*)"trying to add a piece out of bounds\n");
	}
}

PieceType Board_getSquareContent (Coordinate x, Coordinate y)
{
	// check bounds
	if(x >= 0 && x < MORPION_DIM && y >=0 && y < MORPION_DIM){
		return game_board[y][x];
	}else{
		fatalError((const char*)"trying to add a piece out of bounds\n");
	}	
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

/**
 * @brief print a the changed case like {x,y} -> STATE, and its state + print the board
 * 
 * @param [in] x the x coordinate
 * @param [in] y the y coordinate
 * @param [in] change the new state of the case
 */
void printChange(Coordinate x, Coordinate y, PieceType change){
	switch(change){
		case NONE:
			printf("{%d,%d} -> NONE\n", x, y);
			break;
		case CROSS:
			printf("{%d,%d} -> CROSS\n", x, y);
			break;
		case CIRCLE:
			printf("{%d,%d} -> CIRCLE\n", x, y);
			break;

	}
}

int main(int argc, char** argv){
	/*--- INIT ---*/
	log_init(stdout, fopen(getenv("LOG_FILE"), "a"));
	Board_init(&printChange, NULL);


	/*--- CODE ---*/
	TEST_print_board();

	// horizontal wins for cross
	printf("horizontal test\n");
	GameResult result = DRAW;
	game_board[0][0] = CROSS;
	game_board[0][1] = CROSS;
	game_board[0][2] = CROSS;
	TEST_print_board();

	assert_m(isGameFinished(game_board, 0, 1, &result) == true && result == CROSS_WINS, "Horizontal test");

	// vertical wins for circles
	printf("vetical test\n");
	result = DRAW;
	game_board[0][1] = CIRCLE;
	game_board[1][1] = CIRCLE;
	game_board[2][1] = CIRCLE;
	TEST_print_board();

	assert_m(isGameFinished(game_board, 0, 1, &result) == true && result == CIRCLE_WINS, "vertical test");

	// diagonal wins for circles
	printf("diagonal test\n");
	result = DRAW;
	game_board[0][2] = CROSS;
	game_board[1][1] = CROSS;
	game_board[2][0] = CROSS;
	TEST_print_board();

	assert_m(isGameFinished(game_board, 1, 1, &result) == true && result == CROSS_WINS, "diagonal test");

	// test set
	Board_putPiece(2, 2, CROSS);
	assert_m(game_board[2][2] == CROSS, "the {2,2} isn't a CROSS, error on set");

	// test get
	game_board[0][0] = CROSS;
	assert_m(Board_getSquareContent(0, 0) == CROSS, "canno't get the {0,0} as a CROSS");


	/*--- END ---*/
	Board_free();
	return EXIT_SUCCESS;
}
#endif