#include <iostream>
#include "Game.h"
#include "Definitions.h"
#include <Windows.h>

int main(){
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	Game game(SCREEN_WIDTH, SCREEN_HEIGHT, "Jet War");
	PostMessage(GetConsoleWindow(), WM_CLOSE, 0, 0);
	return EXIT_SUCCESS;
}