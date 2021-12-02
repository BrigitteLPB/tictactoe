/**
 * @file main.c
 *
 * @date 7/10/2016
 * @author BrigitteLPB & Matteo LAFAYE
 */

#include "game.h"
#include <stdlib.h>
#include <stdio.h>
#include "log.h"


int main (int argc, char **argv)
{
	/*--- INIT ---*/
	log_init(stdout, fopen(getenv("LOG_FILE"), "a"));
	log_m(INFO, "hello world !");

	Game_init();

	/*--- CODE ---*/
	Game_loop();

	/*--- END ---*/
	Game_free();
	log_free();

	return EXIT_SUCCESS;
}
