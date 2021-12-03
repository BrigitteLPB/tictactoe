/**
 * @file board_view_text.c
 * @author BrigitteLPB & Matteo LAFAYE
 * @brief console implements for graphic functions
 * @date 2021-12-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */
/*--- INCLUDE ---*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "board_view.h"
#include "config.h"
#include "log.h"

#if CONFIG_TEXTUI
/*--- VARS & CONSTS ---*/
static PieceType graph_board[MORPION_DIM][MORPION_DIM] = {0};

/*--- PROTOTYPES ---*/
/**
 * @brief clear the console
 * 
 */
void PRIVATE_BoardView_clear();


/*--- FUNCTIONS ---*/
void PRIVATE_BoardView_clear(){
	#if _WIN32 || _WIN64
		system("cls");
	#elif __unix__
		system("clear");
	#endif
}

void BoardView_init (void)
{
	// init the board
	for(int y=0; y < MORPION_DIM; y++){
		for(int x=0; x <MORPION_DIM; x++){
			graph_board[y][x] = NONE;
		}
	}

	log_m(INFO, "BoardView initialize");
}

void BoardView_free (void)
{
	log_m(INFO, "BoardView free");
}

void BoardView_displayAll (void)
{
	PRIVATE_BoardView_clear();
	for(int y=0; y<MORPION_DIM; y++){
		for(int x=0; x<MORPION_DIM; x++){
			switch(graph_board[y][x]){
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

void BoardView_displaySquare (Coordinate x, Coordinate y, PieceType kindOfPiece)
{
	// add this to the graph_board
	if(x >= 0 && x < MORPION_DIM && y >=0 && y < MORPION_DIM){
		graph_board[y][x] = kindOfPiece;
	}
	
	BoardView_displayAll();	// don't care of where the coord is placed
}

void BoardView_displayEndOfGame (GameResult result)
{
	switch (result)
	{
		case DRAW:
			printf("DRAW !\n");
			break;
	
		case CROSS_WINS:
			printf("CROSS WINS !\n");
			break;
		
		case CIRCLE_WINS:
			printf("CIRCLE WINS !\n");
			break;
	}
}

void BoardView_displayPlayersTurn (PieceType thisPlayer)
{
	// TODO: à compléter
}

void BoardView_sayCannotPutPiece (void)
{
	printf("Canno't put piece here !\n");
}


#if TEST_APP && TEST_boardView
int main(int argc, char** argv){
	/*--- INIT ---*/
	BoardView_init();

	/*--- CODE ---*/
	BoardView_displayAll();
	/** expected :
	 * |.||.||.|
	 * |.||.||.|
	 * |.||.||.|
	 */

	BoardView_displaySquare(0, 0, CROSS);
	/** expected :
	 * |x||.||.|
	 * |.||.||.|
	 * |.||.||.|
	 */

	BoardView_sayCannotPutPiece();
	/** expected :
	 * Canno't put piece here !\n
	 */

	BoardView_displayPlayersTurn(CROSS);
	/** expected :
	 * ??
	 */

	BoardView_displayEndOfGame(CROSS_WINS);
	/** expected :
	 * CROSS WINS !\n
	 */


	/*--- END ---*/
	BoardView_free();
	return EXIT_SUCCESS;
}
#endif
#endif // defined CONFIG_TEXTUI
