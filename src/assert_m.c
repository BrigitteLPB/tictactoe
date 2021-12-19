#include "assert_m.h"
#include "tictactoe_errors.h"

void assert_m(bool condition, const char* message){
	if(!condition){
		fatalError(message);
	}
}
