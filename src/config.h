#ifndef CONFIG_H
	#define CONFIG_H

	#define SDL								0	// use the SDL
	#if !SDL
		#define CONFIG_PLAYER_MANAGER_MOCK	1	// config for player_manager_mock.c
		#define CONFIG_TEXTUI				1	// config for board_view_text.c
	#endif

	#define	MORPION_DIM						3	// largeur et hauteur du morpion


	/*--- TESTS ---*/
	#define TEST_APP						1	// switch the main in test mode

	#define	TEST_log						0	// test log module
	#define	TEST_errors						0	// test errors module
	#define	TEST_board						0	// test errors module
	#define	TEST_boardView					0	// test errors module
	#define	TEST_player_manager_mock		1	// test errors module

	#if TEST_APP && (TEST_log + TEST_errors + TEST_board + TEST_boardView + TEST_player_manager_mock) != 1
		#error	"multiple tests selected"
	#endif

#endif