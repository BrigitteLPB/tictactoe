/**
 * @file player_manager_scanf.c
 *
 * @date 7 oct. 2016
 * @author jilias
 */

#include "board.h"
#include "board_view.h"
#include <assert.h>
#include <stdio.h>

#if defined CONFIG_PLAYER_MANAGER_SCANF

void PlayerManager_init (void)
{
}

void PlayerManager_free (void)
{
}

void PlayerManager_oneTurn (void)
{
  // TODO: à compléter
}

#if TEST_APP && TEST_player_manager_scanf
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
