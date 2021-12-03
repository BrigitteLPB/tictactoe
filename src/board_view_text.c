#include <assert.h>
#include <stdio.h>

#include "board_view.h"
#include "config.h"
#include "log.h"

#if CONFIG_TEXTUI

	void BoardView_init (void)
	{
		
		log_m(INFO, "BoardView initialize");
	}

	void BoardView_free (void)
	{
		
		log_m(INFO, "BoardView free");
	}

	void BoardView_displayAll (void)
	{
		// TODO: à compléter
	}

	void BoardView_displaySquare (Coordinate x, Coordinate y, PieceType kindOfPiece)
	{
		BoardView_displayAll();
	}

	void BoardView_displayEndOfGame (GameResult result)
	{
		switch (result)
		{
			case DRAW:
				printf("DRAW !");
				break;
		
			case CROSS_WINS:
				printf("CROSS WINS !");
				break;
			
			case CIRCLE_WINS:
				printf("CIRCLE WINS !");
				break;
		}
	}

	void BoardView_displayPlayersTurn (PieceType thisPlayer)
	{
		// TODO: à compléter
	}

	void BoardView_sayCannotPutPiece (void)
	{
		// TODO: à compléter
	}

#endif // defined CONFIG_TEXTUI
