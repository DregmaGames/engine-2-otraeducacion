#include "testGame.h"
#include "Renderer.h"
#include "pg1_input.h"
#include "../Scene1.h"
#include "../Scene2.h"
//---------------------------------------
using namespace Juego;
//---------------------------------------
 MyGame::MyGame(){

 }
//bool MyGame::init (pGr::Renderer& rkRenderer)
 bool MyGame::init(pGr::Renderer& rkRenderer,pGr::Importer& rkImporter)
{
	m_kScene = new Scene1();
	m_kScene->m_pkName = "main";
	rkImporter.importScene("assets/Test.xml",*m_kScene);
	currentScene = m_kScene;
	addScene(m_kScene);

	m_Scene2 = new Scene2();
	m_Scene2->m_pkName = "S";
	addScene(m_Scene2);

	/*//m_kScene = Importer.importScene("assets/Test.xml");
	//Quad1
	m_kQuad1.setScale(1000.0f,25.0f);
	m_kQuad1.setPos(-200.0f,-200.0f);
	m_kQuad2.setScale(250.0f,250.0f);
	m_kQuad2.setPos(200.0f,0.0f);
	//Sprite1
	m_kSprite1.setScale(50.0f,100.0f);
	m_kSprite1.setPos(0.0f,0.0f);
	//Seteo Texturas
	pGr::Texture kTexture = rkRenderer.loadTexture("assets/Link.png",PG1_COLOR_RGB(0,255,0));
	m_kSprite1.setTexture(kTexture);
	//Lenght
	m_kIdle.setLength(1500);
	m_kWalk.setLength(1500);
	//AddFrame y SetAnimation
	m_kIdle.addFrame(512.0f,1024.0f,	94.0f,	20.0f,	23.0f,	41.0f);
	m_kIdle.addFrame(512.0f,1024.0f,	94.0f,	20.0f,	23.0f,	41.0f);
	m_kWalk.addFrame(512.0f,1024.0f,	148.0f,	20.0f,	23.0f,	41.0f);
	m_kIdle.addFrame(512.0f,1024.0f,	194.0f,	20.0f,	23.0f,	41.0f);
	m_kSprite1.setAnimation(&m_kIdle);
	m_kSprite.setAnimation(&m_kWalk);
	//*******
	m_kObjects.push_back(m_kQuad1);
	m_kObjects.push_back(m_kQuad2);*/
	return true;
}
//---------------------------------------
void MyGame::frame (pGr::Renderer& rkRenderer, pGr::DirectInput& rkInput,pGr::Timer& rkTimer,pGr::Importer& rkImporter)
{
	/*//handle user input
	static float fSpeed = 1;
	float FPosX = m_kSprite1.posX();
	float FPosY = m_kSprite1.posY();
	//Input Sprite 1
	if(rkInput.keyDown(pGr::Input::KEY_UP)) {
		FPosY += fSpeed;
	}
	if(rkInput.keyDown(pGr::Input::KEY_DOWN)) {
		FPosY -= fSpeed;
	}
	if(rkInput.keyDown(pGr::Input::KEY_RIGHT)) {
		//float a = m_kSprite.m_fScaleX;
		//m_kSprite1.scaleX( a );
		FPosX += fSpeed;
	}
	if(rkInput.keyDown(pGr::Input::KEY_LEFT)) {
		FPosX -= fSpeed;
	}
	m_kSprite1.setPos(FPosX,FPosY);
	//Colisiones
	for (std::list<pGr::Entity2D>::iterator it = m_kObjects.begin(); it != m_kObjects.end(); it++){
		if(m_kSprite1.checkCollision(*it) == pGr::Entity2D::CollisionHorizontal)
		{
			m_kSprite1.returnToPos(m_kSprite1.prevPosX(), m_kSprite1.posY());
		}
		if(m_kSprite1.checkCollision(*it) == pGr::Entity2D::CollisionVertical)
		{
			m_kSprite1.returnToPos(m_kSprite1.posX(), m_kSprite1.prevPosY());
		}
	}*/
	//m_kScene->drawScene(&rkRenderer, &rkTimer);
	//render
	/*m_kSprite1.Update(rkTimer);
	m_kSprite1.draw(rkRenderer);
	m_kQuad1.draw(rkRenderer);
	m_kQuad2.draw(rkRenderer);*/
}
//---------------------------------------
void MyGame::deinit()
{
	delete m_kScene;
}
//---------------------------------------
