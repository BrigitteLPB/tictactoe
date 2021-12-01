/**
 * @file main.c
 *
 * @date 7/10/2016
 * @author Jonathan ILIAS-PILLET & Richard WOODWARD
 */

#include "game.h"
#include <stdlib.h>
#include <stdio.h>

int main (void)
{
	printf("Hello World!\n");	// DEBUG
	
	Game_init ();

	Game_loop ();

	Game_free ();

	return EXIT_SUCCESS;
}
