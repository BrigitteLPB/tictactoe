/**
 * @file main.c
 *
 * @date 7 oct. 2016
 * @author BrigitteLPB & Mattéo LAFAYE
 */
/*--- INCLUDE ---*/
#include <stdio.h>

#include "player_manager.h"
#include "board.h"
#include "board_view.h"
#include "log.h"

/*--- VARS & CONSTS ---*/


/*--- PROTOTYPES ---*/


/*--- FUNCTIONS ---*/
void Game_init (void)
{
	Board_init(
		BoardView_displaySquare,	// affichage des updates
		BoardView_displayEndOfGame	// affichage du résultat
	);
	PlayerManager_init();

	log_m(INFO, "Game initialize");
}

void Game_free (void)
{
	Board_free();
	PlayerManager_free();
	log_m(INFO, "Game free");
}

void Game_loop (void)
{
	log_m(DEBUG, "Game loop");	// DEBUG

	
}
