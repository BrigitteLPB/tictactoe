/**
 * @file tictactoe_erros.c
 *
 * @date 8 oct. 2016
 * @author BrigitteLPB & Matteo LAFAYE
 */

#include "tictactoe_errors.h"
#include <stdio.h>
#include <stdlib.h>
#include "log.h"
#include "config.h"

void fatalError (const char *message)
{
	log_m(ERROR, message);
	fprintf (stderr, "%s\n", message);
	exit (EXIT_FAILURE);
}


#if TEST_APP && TEST_errors
void main(int argc, char** argv){
	/*--- INIT ---*/
	log_init(stdout, fopen((const char*) getenv("LOG_FILE"), "a"));

	/*--- CODE ---*/
	fatalError((const char*) "test message");

	/*--- END ---*/
	log_free();
}
#endif