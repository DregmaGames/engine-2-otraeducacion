#include "Scene3.h"
#include "Renderer.h"
#include "Camera.h"
using namespace Juego;

void Scene3::frame(pGr::Renderer& r ,pGr::Importer& importer, pGr::Game& game, pGr::DirectInput& dInput){
	m_Pkmesh->draw(r);
}


bool Scene3::init(pGr::Renderer& r){
	m_Pkmesh =new pGr::Mesh(r);
	return true;
}
