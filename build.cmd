@REM gcc src/main.c -IC:/Users/BrigitteLPB/OneDrive/CODE/C/pongSDL/libs/SDL2-2.0.18/i686-w64-mingw32/include/SDL2 -LC:/Users/BrigitteLPB/OneDrive/CODE/C/pongSDL/libs/SDL2-2.0.18/i686-w64-mingw32/lib -lmingw32 -lSDL2main -lSDL2 -mwindows -o build/pongSDL.exe 
cmake -D INPUT_NAME=tictactoe -D CMAKE_BUILD_TYPE=Release -S ./ -B ./build -G "MinGW Makefiles"
cmake --build ./build