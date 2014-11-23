//----------------------------
#include "Engine.h"
#include "testGame.h"
using namespace Juego;
//---------------------------
//winMain
int WINAPI WinMain(HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR lpCmdLine , int intnShowCmd){
	pGr::Engine eng(hInstance,1280,920);
	eng.init();
	eng.pgGame = new MyGame();
	eng.run();
}