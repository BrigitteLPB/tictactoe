/**
 * @file player_manager_mock.c
 *
 * @date 7 oct. 2016
 * @author jilias
 */
#include "config.h"
#if CONFIG_PLAYER_MANAGER_MOCK

#include "board.h"
#include <assert.h>
#include <stdio.h>


void PlayerManager_init (void)
{
}

void PlayerManager_free (void)
{
}

void PlayerManager_oneTurn (void)
{
  /* TODO: à compléter */
}

#if TEST_APP && TEST_player_manager_mock
int main(int argc, char **argv){
	/*--- INIT --*/
	PlayerManager_init();


	/*--- CODE ---*/
	printf("ret: %d\n", PRIVATE_PlayerManager_input_int(stdin, stdout, "int:"));

	/*--- END ---*/
	PlayerManager_free();
	return EXIT_SUCCESS;  
}
#endif
#endif //  #if defined CONFIG_PLAYER_MANAGER_MOCK
