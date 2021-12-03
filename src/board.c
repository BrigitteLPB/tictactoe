/*--- INCLUDE ---*/
#include <assert.h>
#include <stdlib.h>
#include "board.h"
#include "board_view.h"
#include "config.h"

#include "log.h"

/*--- VARS AND CONSTS ---*/
static PieceType **game_board;


/*--- FUNCTIONS ---*/

/**
 * Check if the game has to be ended. Only alignment from the last
 * modified square are checked.
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
	// TODO: à compléter
}


void Board_init (SquareChangeCallback onSquareChange, EndOfGameCallback onEndOfGame)
{
	// init the var
	game_board = (void *) calloc(MORPION_DIM * MORPION_DIM, sizeof(PieceType));

	BoardView_init();
	log_m(INFO, "Board initialize");
}


void Board_free ()
{
	free(game_board);
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
