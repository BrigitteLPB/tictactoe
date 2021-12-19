/**
 * @file main.c
 *
 * @date 7/10/2016
 * @author BrigitteLPB & Matteo LAFAYE
 */

#include <stdlib.h>
#include <stdio.h>
#include "config.h"

#include "game.h"
#include "log.h"


#if !TEST_APP
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
#endif
