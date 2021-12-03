/**
 * @file player_manager_mock.c
 *
 * @date 7 oct. 2016
 * @author BrigitteLPB & Matteo LAFAYE
 */
/*--- INCLUDE ---*/
#include "board.h"
#include <assert.h>
#include <stdio.h>
#include "config.h"

#include "log.h"


/*--- VARS and CONSTS ---*/



/*--- FUNCTIONS ---*/
#if CONFIG_PLAYER_MANAGER_MOCK

void PlayerManager_init (void)
{
	log_m(INFO, "PlayerManager initialize");
}

void PlayerManager_free (void)
{
	log_m(INFO, "PlayerManager free");
}

void PlayerManager_oneTurn (void)
{
	// TODO
}

#endif //  #if defined CONFIG_PLAYER_MANAGER_MOCK
