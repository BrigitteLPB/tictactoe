/**
 * @file main.c
 *
 * @date 7 oct. 2016
 * @author BrigitteLPB & Mattéo LAFAYE
 */
/*--- INCLUDE ---*/
#include <stdio.h>

#include "config.h"
#include "player_manager.h"
#include "board.h"
#include "board_view.h"
#include "log.h"

/*--- VARS & CONSTS ---*/
static bool endOfGame = false;


/*--- PROTOTYPES ---*/
/**
 * @brief callback for change in piece
 * 
 * @param [in] x x position [0..MORPION_DIM-1] 
 * @param [in] y y position [0..MORPION_DIM-1] 
 * @param piece the kind of piece to change
 */
static void PRIVATE_GAME_change_cb(Coordinate x, Coordinate y, PieceType piece);

/**
 * @brief manage the end of the game
 * 
 * @param [in] result the result of the game
 */
static void PRIVATE_GAME_end_of_game_cb(GameResult result);

/*--- FUNCTIONS ---*/
static void PRIVATE_GAME_change_cb(Coordinate x, Coordinate y, PieceType piece){
	PieceType on_board =  Board_getSquareContent(x, y);
	if(x < 0 || x >= MORPION_DIM || y < 0 || y >= MORPION_DIM || (on_board != piece && on_board != NONE)){
		BoardView_sayCannotPutPiece();
	}else{
		BoardView_displaySquare(x, y, piece);
	}
}

static void PRIVATE_GAME_end_of_game_cb(GameResult result){
	endOfGame = true;
	BoardView_displayEndOfGame(result);
}

void Game_init (void)
{
	Board_init(
		&PRIVATE_GAME_change_cb,	// affichage des updates
		&PRIVATE_GAME_end_of_game_cb	// affichage du résultat
	);
	BoardView_init();
	PlayerManager_init();

	log_m(INFO, "Game initialize");
}

void Game_free (void)
{
	Board_free();
	BoardView_free();
	PlayerManager_free();
	log_m(INFO, "Game free");
}

void Game_loop (void)
{
	log_m(DEBUG, "Game loop");	// DEBUG
	
	while(!endOfGame){
		PlayerManager_oneTurn();
	}
}

