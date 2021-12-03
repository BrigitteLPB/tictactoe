#ifndef CONFIG_H
	#define CONFIG_H


	#define CONFIG_PLAYER_MANAGER_MOCK		0	// config for player_manager_mock.c
	#define CONFIG_TEXTUI					1	// config for board_view_text.c

	#define	MORPION_DIM						3	// largeur et hauteur du morpion


	/*--- TESTS ---*/
	#define TEST_APP						1	// switch the main in test mode

	#define	TEST_log						0	// test log module
	#define	TEST_errors						1	// test errors module

	#if (TEST_log + TEST_errors) > 1
		#error	"multiple tests selected"
	#endif

#endif