/**
 * @file player_manager_mock.c
 *
 * @date 7 oct. 2016
 * @author BrigitteLPB & Matteo LAFAYE
 */
/*--- INCLUDE ---*/
#include "config.h"
#include "board.h"
#include "assert_m.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "log.h"


/*--- VARS and CONSTS ---*/
#define MAX_INPUT_CHAR				128		// max size of the input str

/**
 * Pointer of a function that can be called when after a player input a coordonate.
 *
 * @param [in] x the board's column where the square is
 * @param [in] y the board's row where the square is
 * @param [in] newContent the player symbol
 */
typedef PutPieceResult (*ProcessPlayerInputCallback) (Coordinate x, Coordinate y, PieceType player);

static ProcessPlayerInputCallback input_cb = NULL;
static PieceType current_player = NONE;		// the player turn

/**
 * @brief move the cursor in console to the x, y position
 * 
 * @param [in] x the horizontal coordonate [1..+inifity]
 * @param [in] y the vertical coordonate [1..+infinity]
 */
#define gotoxy(x,y) printf("\033[%d;%dH", (x), (y))

#if CONFIG_PLAYER_MANAGER_MOCK
/*--- PROTOTYPES ---*/
/**
 * 
 * @brief get a int from the user
 * 
 * @param [in] flux_in the FILE to read
 * @param [in] flux_out the FILE to write
 * @param [in] message the message to display when asking
 * @return int the value select != 0
 */
int PRIVATE_PlayerManager_input_int(FILE *flux_in, FILE *flux_out, const char *message);

/**
 * @brief remove the enters in the str
 * 
 * @param [in,out] str the specified str
 */
void PRIVATE_PlayerManager_removeEnters(char str[]);



/*--- FUNCTIONS ---*/
int PRIVATE_PlayerManager_input_int(FILE *flux_in, FILE *flux_out, const char *message){
	char input_user[MAX_INPUT_CHAR] = "";
	int ret_val = 0;

	while (true){
		fprintf(flux_out, "%s", message);
		fflush(flux_out);
		fgets(input_user, MAX_INPUT_CHAR, flux_in);
		PRIVATE_PlayerManager_removeEnters(input_user);
		ret_val = atoi(input_user);
		if(ret_val != 0){
			return ret_val;
		}

		// clear the line
		// for(int i=0; input_user[i] != '\0'; i++){
		// 	input_user[i] = ' ';
		// }
		// gotoxy(1,1);
		// fprintf(flux_out, "\r%s\r", input_user);
	}
}

void PRIVATE_PlayerManager_removeEnters(char str[]){
	//init
	int length_str = (int) (strlen(str));
	int i = 0, str_pos = 0;

	//code
	for (i=0;i<length_str;i++){
		if (str[i] != '\n'){
			str[str_pos] = str[i];
			str_pos++;
		}
	}
	str[length_str-1] = '\0';
}

void PlayerManager_init (void)
{
	input_cb = &Board_putPiece;
	current_player = CROSS;
	log_m(INFO, "PlayerManager initialize");
}

void PlayerManager_free (void)
{
	input_cb = NULL;
	current_player = NONE;
	log_m(INFO, "PlayerManager free");
}

void PlayerManager_oneTurn (void)
{
	if(current_player != NONE){

	}

	switch(current_player){
		
	}
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
