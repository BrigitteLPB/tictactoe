/**
 * @file player_manager_mock.c
 *
 * @date 7 oct. 2016
 * @author BrigitteLPB & Matteo LAFAYE
 */
/*--- INCLUDE ---*/
#include "config.h"
#include "board.h"
#include "board_view.h"
#include "assert_m.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "tictactoe_errors.h"

#include "log.h"


/*--- VARS and CONSTS ---*/
#define MAX_INPUT_CHAR				128		// max size of the input str

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
	current_player = CROSS;
	log_m(INFO, "PlayerManager initialize");
}

void PlayerManager_free (void)
{
	current_player = NONE;
	log_m(INFO, "PlayerManager free");
}

void PlayerManager_oneTurn (void)
{
	if(current_player != NONE){
		int x_pos;
		int y_pos;
		do{
			BoardView_displayPlayersTurn(current_player);
			
			do{
				x_pos = PRIVATE_PlayerManager_input_int(stdin, stdout, "X position [1..3]: ");
			}while(x_pos < 0 || x_pos > MORPION_DIM);

			do{
				y_pos = PRIVATE_PlayerManager_input_int(stdin, stdout, "Y position [1..3]: ");
			}while(y_pos < 0 || y_pos > MORPION_DIM);

		}while(Board_putPiece(x_pos-1, y_pos-1, current_player) == SQUARE_IS_NOT_EMPTY);
	}

	// switching to other player
	switch(current_player){
		case CROSS:
			current_player = CIRCLE;
			break;
		case CIRCLE:
			current_player = CROSS;
			break;
		default:
			fatalError("[playerManager] Undifined token for the player");
			break;
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
