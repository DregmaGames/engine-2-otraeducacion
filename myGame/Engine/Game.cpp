#include "Game.h"
#include "Scene.h"
#include "Importer.h"
using namespace pGr;

Game::Game() : done(false)
{
	//NOTHING TO DO HERE / NOPE.avi
}


void Game::setDone(bool auxDone)
{
	done = auxDone;
}

bool Game::getDone()
{
	return done;
}
