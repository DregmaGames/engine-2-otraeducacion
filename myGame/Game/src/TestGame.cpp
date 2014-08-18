#include "testGame.h"
#include "Renderer.h"
#include "pg1_input.h"
#include "Scene1.h"
#include "Scene2.h"
//---------------------------------------
using namespace Juego;
//---------------------------------------
 MyGame::MyGame(){
 }
 bool MyGame::init(pGr::Renderer& rkRenderer,pGr::Importer& rkImporter)
{
	m_kScene = new Scene1();
	m_kScene->m_pkName = "main";
	rkImporter.importScene("assets/Test.xml",*m_kScene);
	currentScene = m_kScene;
	addScene(m_kScene);

	m_kScene1 = new Scene2();
	m_kScene1->m_pkName = "S";
	addScene(m_kScene1);
	return true;
}
//---------------------------------------
void MyGame::frame (pGr::Renderer& rkRenderer, pGr::DirectInput& rkInput,pGr::Timer& rkTimer,pGr::Importer& rkImporter)
{
}
//---------------------------------------
void MyGame::deinit()
{
	delete m_kScene;
	delete m_kScene1;
}
//---------------------------------------
