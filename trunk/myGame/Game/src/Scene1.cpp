#include "Scene1.h"
#include "Renderer.h"
#include "Camera.h"
using namespace Juego;
void Scene1::frame(pGr::Renderer& r ,pGr::Importer& importer, pGr::Game& game, pGr::DirectInput& dInput){
	if(dInput.keyDown(pGr::Input::KEY_DOWN)){
		_Quad->setPos(_Quad->posX(),_Quad->posY() - 1,_Quad->posZ());
	}

	//Camdbiar escena
	if(dInput.keyDown(pGr::Input::KEY_1)){
		game.setCurrentScene("S",importer,"assets/Test.xml");
	}
}

bool Scene1::init(){
	getEntity(&_Quad,"floor");
	return true;
}