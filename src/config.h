#ifndef CONFIG_H
	#define CONFIG_H

	#define CONFIG_SDLUI					0	// use the SDL
	#if !CONFIG_SDLUI
		#define CONFIG_PLAYER_MANAGER_MOCK	1	// config for player_manager_mock.c
		#define CONFIG_PLAYER_MANAGER_SCNAF	1	// config for player_manager_scanf.c
		#define CONFIG_TEXTUI				1	// config for board_view_text.c
	#endif

	#define	MORPION_DIM						3	// largeur et hauteur du morpion


	/*--- TESTS ---*/
	#define TEST_APP						1	// switch the main in test mode

	#define	TEST_log						0	// test log module
	#define	TEST_errors						0	// test errors module
	#define	TEST_board						0	// test board module
	#define	TEST_boardView					0	// test board_view module
	#define	TEST_board_view_sdl				0	// test board_view_sdl module
	#define	TEST_player_manager_mock		1	// test player_manager_mock module
	#define TEST_player_manager_scanf		0	// test player_manager_scanf
	#define TEST_player_manager_sdl			0	// test player_manager_sdl
	#define TEST_check_end_of_game			0	// test CheckEndOfGame

	#if TEST_APP && (TEST_log + TEST_errors + TEST_board + TEST_boardView + TEST_player_manager_mock + TEST_board_view_sdl + TEST_player_manager_scanf + TEST_player_manager_sdl + TEST_check_end_of_game) != 1
		#error	"multiple tests selected"
	#endif

#endif