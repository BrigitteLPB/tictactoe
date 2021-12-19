/**
 * @file board_view_text.c
 *
 * @date 7 oct. 2016
 * @author jilias
 */
#include "config.h"
#if CONFIG_SDLUI

/*--- INCLUDE ---*/
#include "board_view.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "tictactoe_errors.h"
#include "log.h"
#include <SDL.h>
#include <SDL_image.h>



/*--- VARS & CONSTS ---*/
// static PieceType graph_board[MORPION_DIM][MORPION_DIM] = {0};

static SDL_Window *MainWindow;
static SDL_Renderer *MainRenderer;
static SDL_Surface *BackgroundImage;
static SDL_Surface *SpriteO;
static SDL_Surface *SpriteX;
static SDL_Surface *SpriteWin;
static SDL_Surface *SpriteDraw;

/*--- FONCTIONS ---*/
/**
 * @brief render a image with SDL position
 * 
 * @param [in] image pointer to a SDL IMG 
 * @param [in] x x pos 
 * @param [in] y y pos
 */
static void renderImage_truePos (SDL_Surface *image, int x, int y)
{
	SDL_Texture *aTexture;
	aTexture = SDL_CreateTextureFromSurface(MainRenderer, image);
	assert (aTexture != NULL);
	SDL_Rect pos = {
		x, 
		y, 
		image->w, 
		image->h
	};

	SDL_RenderCopy(MainRenderer, aTexture, 0, &pos);
	SDL_RenderPresent(MainRenderer);
	SDL_DestroyTexture(aTexture);
}

/**
 * @brief render a image
 * 
 * @param [in] image pointer to a SDL IMG 
 * @param [in] x x pos [0..2] 
 * @param [in] y y pos [0..2] 
 */
static void renderImage (SDL_Surface *image, int x, int y)
{
	renderImage_truePos(image, x*(WINDOWS_HEIGHT/MORPION_DIM), y*(WINDOWS_HEIGHT/MORPION_DIM));
}

void BoardView_init (void)
{
		int result;

		// init module board
		// for(int y=0; y<MORPION_DIM; y++){
		// 	for(int x=0; x<MORPION_DIM; x++){
		// 		graph_board[y][x] = NONE;
		// 	}
		// }

		// Initialize SDL
		result = SDL_Init (SDL_INIT_VIDEO);
		if (result != 0)
		{
			fatalError (SDL_GetError ());
		}
		atexit (SDL_Quit);

		// Initialize SDL_image
		int initted=IMG_Init(IMG_INIT_PNG);
		if (initted != IMG_INIT_PNG)
		{
			fatalError(IMG_GetError ());
		}

		// Loads images
		BackgroundImage = IMG_Load (ASSET_BACKGROUND);
		if (BackgroundImage == NULL)
					fatalError(IMG_GetError ());
		SpriteO = IMG_Load (ASSET_CIRCLE);
		if (SpriteO == NULL)
					fatalError(IMG_GetError ());
		SpriteX = IMG_Load (ASSET_CROSS);
		if (SpriteX == NULL)
			fatalError(IMG_GetError ());
		SpriteWin = IMG_Load (ASSET_WIN);
		if (SpriteWin == NULL)
			fatalError(IMG_GetError ());
		SpriteDraw = IMG_Load (ASSET_DRAW);
		if (SpriteDraw == NULL)
			fatalError(IMG_GetError ());


		// Creates the window
		MainWindow = SDL_CreateWindow (APP_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOWS_WIDTH, WINDOWS_HEIGHT, 0);
		if (MainWindow == NULL)
		{
			fatalError (SDL_GetError ());
		}

		// Creates the main renderer
		MainRenderer = SDL_CreateRenderer(MainWindow, -1, SDL_RENDERER_ACCELERATED);
		if (MainRenderer == NULL)
		{
			fatalError(SDL_GetError());
		}

		// init screen
		BoardView_displayAll();
}

void BoardView_free (void)
{
	SDL_DestroyRenderer(MainRenderer);
	SDL_DestroyWindow(MainWindow);
	SDL_FreeSurface(SpriteX);
	SDL_FreeSurface(SpriteO);
	SDL_FreeSurface(BackgroundImage);
	IMG_Quit ();
	SDL_Quit ();
}

void BoardView_displayAll (void)
{
	renderImage_truePos(BackgroundImage,0,0);
	/* utiliser "renderImage" pour afficher l'image de fond "BackgroundImage",
	 * puis afficher l'ensemble des cases à l'aide de la fonction BoardView_displaySquare
	 */
}

void BoardView_displaySquare (Coordinate x, Coordinate y, PieceType kindOfPiece)
{
	switch(kindOfPiece){
		case CROSS:
			renderImage(SpriteX,x,y);
			break;
		case CIRCLE:
			renderImage(SpriteO,x,y);
			break;
	}
	/* utiliser "renderImage" pour afficher le sprite correspondant à kindOfPiece à
	 * l'endroit correspondant aux coordonnées logiques "x" et "y".
	 */
}

void BoardView_displayEndOfGame (GameResult result)
{
	renderImage_truePos(BackgroundImage, 0, 0);
	switch(result){
		case DRAW:
			renderImage_truePos(SpriteDraw, (WINDOWS_WIDTH - SpriteDraw->w)/2, (WINDOWS_HEIGHT - SpriteDraw->h)/2);
			break;
		case CIRCLE_WINS:
			renderImage(SpriteO, 1, 0);
			renderImage_truePos(SpriteWin, (WINDOWS_WIDTH - SpriteWin->w)/2, (WINDOWS_HEIGHT - SpriteWin->h)/2);
			break;
		case CROSS_WINS:
			renderImage(SpriteX, 1, 0);
			renderImage_truePos(SpriteWin, (WINDOWS_WIDTH - SpriteWin->w)/2, (WINDOWS_HEIGHT - SpriteWin->h)/2);
			break;
	}

	bool validMove = false;
	SDL_Event event;

	do{
		int error = SDL_WaitEvent (&event);
		if(error == 0){
			fatalError("error during SDL_WaitEvent (BoardView_displayEndOfGame)");
		}
		
		switch (event.type)
		{
			case SDL_QUIT:
			case SDL_MOUSEBUTTONDOWN:
				validMove = true;
				break;
		}
	}
	while (!validMove);
}

void BoardView_displayPlayersTurn (PieceType thisPlayer)
{
	BoardView_displayAll();
	switch(thisPlayer){
		case CROSS:
			printf("CROSS turn\n");		// TODO text SDL
			break;
		case CIRCLE:
			printf("CRICLE turn\n");	// TODO test SDL
			break;
	}}

void BoardView_sayCannotPutPiece (void)
{
	// TODO: vous pouvez améliorer ceci (lorsque le reste fonctionnera)
}

#if TEST_APP && TEST_board_view_sdl
int main(int argc, char** argv){
	/*--- INIT ---*/
	BoardView_init();

	/*--- CODE ---*/
	BoardView_displayEndOfGame(CIRCLE_WINS);

	/*--- END ---*/
	BoardView_free();
	return EXIT_SUCCESS;
}
#endif
#endif // defined CONFIG_SDLUI
