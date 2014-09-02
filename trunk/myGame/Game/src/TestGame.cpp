#include "testGame.h"
#include "Renderer.h"
#include "pg1_input.h"

//---------------------------------------
using namespace Juego;
//---------------------------------------
 MyGame::MyGame(){
 }
 bool MyGame::init(pGr::Renderer& rkRenderer,pGr::Importer& rkImporter)
{
	m_kScene = new Scene2();
	m_kScene->m_pkName = "Main";
	addScene(m_kScene);

	currentScene = m_kScene;
	return true;
}
//---------------------------------------
void MyGame::frame (pGr::Renderer& rkRenderer, pGr::DirectInput& rkInput,pGr::Timer& rkTimer,pGr::Importer& rkImporter)
{
}
//---------------------------------------
void MyGame::deinit()
{
	if(m_kScene){
		m_kScene=NULL;
		delete m_kScene;
	}
}
//---------------------------------------
