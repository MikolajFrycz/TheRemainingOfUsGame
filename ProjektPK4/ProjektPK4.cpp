#include "Game.h"


#ifdef _DEBUG
	int main()
#else
#include <Windows.h>
	int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
#endif


{
	Game game;

	game.run();

	return 0;
}