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
 * @brief check if there is a place available
 * 
 * @param [in] boardSquares the board to process
 * @return true the board is complete
 * @return false there is one or more NONE in the board 
 */
static bool isDraw(const PieceType boardSquares[MORPION_DIM][MORPION_DIM]){
	for(int y=0; y<MORPION_DIM; y++){
		for(int x=0; x<MORPION_DIM; x++){
			if(boardSquares[y][x] == NONE){
				return false;
			}
		}
	}
	return true;
}


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

	typedef enum {
		MOINS_1,
		MOINS_0,
		PLUS_1
	} pos_index_e;

	Coordinate x[] = {	// pos [x-1, x, x+1]
		(lastChangeX == 0)?(lastChangeX -1 + MORPION_DIM)%MORPION_DIM : (lastChangeX -1)%MORPION_DIM,
		lastChangeX,
		(lastChangeX +1)%MORPION_DIM
	};

	Coordinate y[] = {	// pos [y-1, y, y+1]
		(lastChangeY == 0)?(lastChangeY -1 + MORPION_DIM)%MORPION_DIM : (lastChangeY -1)%MORPION_DIM,
		lastChangeY,
		(lastChangeY +1)%MORPION_DIM
	};


	// l'algorythme est concue pour un jeu 3x3
	// bool v = (boardSquares[lastChangeY][lastChangeX] == 		// vertical
	// 				boardSquares[(lastChangeY -1)%MORPION_DIM][(lastChangeX)%MORPION_DIM] ==
	// 				boardSquares[(lastChangeY +1)%MORPION_DIM][(lastChangeX)%MORPION_DIM] !=
	// 				NONE
	// );

	bool v = (boardSquares[y[MOINS_0]][x[MOINS_0]] == boardSquares[y[MOINS_1]][x[MOINS_0]] &&
				boardSquares[y[MOINS_0]][x[MOINS_0]] == boardSquares[y[PLUS_1]][x[MOINS_0]] &&
				boardSquares[y[MOINS_0]][x[MOINS_0]] != NONE
	);

	bool h = (boardSquares[y[MOINS_0]][x[MOINS_0]] == boardSquares[y[MOINS_0]][x[MOINS_1]] &&
				boardSquares[y[MOINS_0]][x[MOINS_0]] == boardSquares[y[MOINS_0]][x[PLUS_1]] &&
				boardSquares[y[MOINS_0]][x[MOINS_0]] != NONE
	);

	// printf("X:%d,Y:%d, X-1:%d,Y-1:%d, X+1:%d,Y+1:%d\n", lastChangeX,lastChangeY, 
	// 													((long) lastChangeY -1)%MORPION_DIM, ((long) lastChangeX -1)%MORPION_DIM,
	// 													((long) lastChangeY +1)%MORPION_DIM,((long) lastChangeX +1)%MORPION_DIM
	// );

	bool dGD = (boardSquares[y[MOINS_0]][x[MOINS_0]] == boardSquares[y[MOINS_1]][x[MOINS_1]] &&
				boardSquares[y[MOINS_0]][x[MOINS_0]] == boardSquares[y[PLUS_1]][x[PLUS_1]] &&
				boardSquares[y[MOINS_0]][x[MOINS_0]] != NONE &&
				x[MOINS_0] == y[MOINS_0]);
			
	bool dDG = (boardSquares[y[MOINS_0]][x[MOINS_0]] == boardSquares[y[PLUS_1]][x[MOINS_1]] &&
				boardSquares[y[MOINS_0]][x[MOINS_0]] == boardSquares[y[MOINS_1]][x[PLUS_1]] &&
				boardSquares[y[MOINS_0]][x[MOINS_0]] != NONE &&
				x[MOINS_0] + y[MOINS_0] == MORPION_DIM-1);

	bool d = dGD || dDG;

	bool win = v || h || d;

	if(win){
		switch(boardSquares[y[MOINS_0]][x[MOINS_0]]){
			case CROSS:
				*gameResult = CROSS_WINS;
				break;
			case CIRCLE:
				*gameResult = CIRCLE_WINS;
				break;
			default:
				*gameResult = DRAW;
				break;
		}
		
		return win;	// always true
	}else{
		*gameResult = DRAW;
		return isDraw(boardSquares);
	}
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

	log_m(INFO, "Board initialize");
}


void Board_free ()
{
	log_m(INFO, "Board free");
}

PutPieceResult Board_putPiece (Coordinate x, Coordinate y, PieceType kindOfPiece)
{
	PutPieceResult ret = SQUARE_IS_NOT_EMPTY;
	// check bounds
	if(x >= 0 && x < MORPION_DIM && y >=0 && y < MORPION_DIM){
		
		if(kindOfPiece != NONE){
			if(game_board[y][x] == NONE){
				game_board[y][x] = kindOfPiece;
				ret = PIECE_IN_PLACE;
				

				GameResult res = DRAW;
				if(isGameFinished(game_board, x, y, &res) && onEndOfGame_cb != NULL){
					onEndOfGame_cb(res);
					return ret;	// on break ici pour ne pas faire tourner le onSquareChange
				}
			}
		}

		// calling the on change callbacks
		if(onSquareChange_cb != NULL){
			onSquareChange_cb(x, y, kindOfPiece);	
		}

		return ret;
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
// TEST_check_end_of_game
typedef struct
{
	PieceType board[3][3];
	Coordinate lastPutX;
	Coordinate lastPutY;
	bool expectedEndOfGameResult;
	GameResult expectedGameResult;
} BoardDataTest;

static const BoardDataTest DataTest[] =
{
{
{
{NONE, NONE, NONE},
{NONE, NONE, NONE},
{NONE, NONE, NONE}}, 0, 0, false, DRAW},
{
{
{NONE, NONE, NONE},
{NONE, CROSS, NONE},
{NONE, NONE, NONE}}, 0, 0, false, DRAW},
{
{
{NONE, NONE, NONE},
{NONE, CIRCLE, NONE},
{NONE, NONE, NONE}}, 1, 1, false, DRAW},
{
{
{CROSS, NONE, NONE},
{CROSS, CIRCLE, NONE},
{NONE, NONE, NONE}}, 0, 1, false, DRAW},
{
{
{CROSS, NONE, NONE},
{CROSS, CIRCLE, CIRCLE},
{NONE, CROSS, NONE}}, 1, 2, false, DRAW},
{
{
{CROSS, NONE, NONE},
{CIRCLE, CIRCLE, NONE},
{NONE, NONE, CROSS}}, 2, 2, false, DRAW},
{
{
{CROSS, NONE, NONE},
{CROSS, CIRCLE, CIRCLE},
{CROSS, NONE, NONE}}, 0, 1, true, CROSS_WINS},
{
{
{CROSS, NONE, NONE},
{CIRCLE, CIRCLE, CIRCLE},
{CROSS, NONE, NONE}}, 2, 1, true, CIRCLE_WINS},
{
{
{CROSS, NONE, NONE},
{CIRCLE, CROSS, CIRCLE},
{NONE, NONE, CROSS}}, 0, 0, true, CROSS_WINS},
{
{
{CROSS, NONE, CIRCLE},
{CROSS, CIRCLE, NONE},
{CIRCLE, NONE, CROSS}}, 1, 1, true, CIRCLE_WINS},
{
{
{CIRCLE, CROSS, CIRCLE},
{CIRCLE, CROSS, CIRCLE},
{CROSS, CIRCLE, CROSS}}, 2, 0, true, DRAW}

};

void testCheckEndOfGame (void)
{
	int successCount = 0;
	int failCount = 0;

	GameResult gameResult;
	bool end;

	for (int i = 0; i < (sizeof(DataTest) / sizeof(BoardDataTest)); i++)
	{
		end = isGameFinished (DataTest[i].board, DataTest[i].lastPutX, DataTest[i].lastPutY, &gameResult);
		if (end != DataTest[i].expectedEndOfGameResult)
		{
			printf ("test #%d failed, expected end of game was %s\n", i,
					DataTest[i].expectedEndOfGameResult ? "true" : "false");
			failCount++;
		}
		else
		{
			successCount++;
		}
		if (end)
		{
			if (gameResult != DataTest[i].expectedGameResult)
			{
				printf ("test #%d failed, expected result of game was %s\n",	i,
						DataTest[i].expectedGameResult == CROSS_WINS ?
								"CROSS_WINS" :
						DataTest[i].expectedGameResult == CIRCLE_WINS ?
								"CIRCLE_WINS" : "DRAW");
				failCount++;
			}
			else
			{
				successCount++;
			}
		}
	}

	printf ("*********\n%d of %d test cases succeeded\n",
			successCount, successCount + failCount);
}



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

	assert_m(isGameFinished(game_board, 1, 0, &result) == true && result == CROSS_WINS, "Horizontal test");

	// vertical wins for circles
	printf("vetical test\n");
	result = DRAW;
	game_board[0][1] = CIRCLE;
	game_board[1][1] = CIRCLE;
	game_board[2][1] = CIRCLE;
	TEST_print_board();

	assert_m(isGameFinished(game_board, 1, 0, &result) == true && result == CIRCLE_WINS, "vertical test");

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


	// test endCheckOfGame
	printf("test CheckEndOfGame\n");
	testCheckEndOfGame();

	/*--- END ---*/
	Board_free();
	return EXIT_SUCCESS;
}
#endif