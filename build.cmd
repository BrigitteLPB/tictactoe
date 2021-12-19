cmake -D INPUT_NAME=tictactoe -D CMAKE_BUILD_TYPE=Release -S ./ -B ./build -G "MinGW Makefiles"
cmake --build ./build