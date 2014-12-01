//----------------------------
#include "Engine.h"
#include "testGame.h"
using namespace Juego;
//---------------------------
//winMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int intnShowCmd){
	pGr::Engine eng(hInstance, 800, 600);
	eng.init();
	MyGame* game = new MyGame();
	eng.setGame(game);
	eng.run();
}