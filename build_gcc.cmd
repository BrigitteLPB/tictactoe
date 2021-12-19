@REM clean
del .\\build /f /s /q

@REM Make build directory
mkdir build

@REM moving assets files
robocopy .\assets .\build\assets **.* /e /j /purge
if %ERRORLEVEL% GEQ 9 exit /b 1

@REM moving .dll
robocopy .\libs\SDL2-2.0.18\i686-w64-mingw32\bin .\build **.dll /j
if %ERRORLEVEL% GEQ 9 exit /b 1
robocopy .\libs\SDL2_image-2.0.5\i686-w64-mingw32\bin .\build **.dll /j
if %ERRORLEVEL% GEQ 9 exit /b 1


@REM GCC command
gcc src/main.c src/board.c src/assert_m.c src/board_view_sdl.c src/board_view_text.c src/game.c src/player_manager_mock.c src/player_manager_scanf.c src/player_manager_sdl.c src/test_CheckEndOfGame.c src/tictactoe_errors.c src/log.c -Ilibs\SDL2_image-2.0.5\i686-w64-mingw32\include\SDL2 -Ilibs\SDL2-2.0.18\i686-w64-mingw32\include\SDL2 -Llibs\SDL2-2.0.18\i686-w64-mingw32\lib -Llibs\SDL2_image-2.0.5\i686-w64-mingw32\lib -lSDL2main -lSDL2 -lSDL2_image -o build/tictactoe.exe
