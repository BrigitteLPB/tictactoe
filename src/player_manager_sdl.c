/**
 * @file player_manager_scanf.c
 *
 * @date 7 oct. 2016
 * @author jilias
 */

#include "board.h"
#include "board_view.h"
#include <assert.h>
#include <SDL.h>
#include <stdbool.h>

#if defined CONFIG_PLAYER_MANAGER_SDL
void PlayerManager_init (void)
{
	assert (SDL_WasInit (SDL_INIT_VIDEO) != 0);
}

void PlayerManager_free (void)
{
}

static bool tryMove (int x, int y)
{
	if((x>153 && x<163) || (x>316 && x<326) || (y>153 && y<163) || (y>316 && y<326) ){
		BoardView_sayCannotPutPiece();
		return false;
	}
	//FONCTION NE FONCTIONNANT PAS, VERIFIER KindOfPiece
	Board_putPiece(x,y,kindofPiece)
	return true;
}

void PlayerManager_oneTurn (void)
{
	int error;
	SDL_Event event;
	bool validMove;

	do
	{
		validMove = false;
		error = SDL_WaitEvent (&event);
		assert (error == 1);
		switch (event.type)
		{
			case SDL_WINDOWEVENT_CLOSE:
				BoardView_free();
				break;
			case SDL_MOUSEBUTTONDOWN:
				validMove = tryMove(event.motion.x,event.motion.y);
				break;
		}
	}
	while (!validMove);
}

#if TEST_APP && TEST_player_manager_sdl
int main(int argc, char **argv){
	/*--- INIT --*/
	PlayerManager_init();


	/*--- CODE ---*/


	/*--- END ---*/
	PlayerManager_free();
	return EXIT_SUCCESS;  
}
#endif
#endif // defined CONFIG_PLAYER_MANAGER_SCANF
