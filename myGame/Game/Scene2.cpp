#include "Scene2.h"
#include<sstream>
#include<string>
#include "Node.h"

pGr::ColorVertex VBuffer[] = {

	{-0.5f, 0.5f, -0.5f, D3DCOLOR_XRGB( 255, 0, 0 )}, // 0 
	{0.5f, 0.5f, -0.5f, D3DCOLOR_XRGB( 0, 0, 255 )}, // 1 
	{ 0.5f, 0.5f, 0.5f, D3DCOLOR_XRGB( 0, 0, 255 )}, // 2 
	{ -0.5f, 0.5f, 0.5f, D3DCOLOR_XRGB( 255, 0, 0 )}, // 3

	{ -0.5f, -0.5f, 0.5f, D3DCOLOR_XRGB( 255, 0, 0 )}, // 4
	{  0.5f, -0.5f, 0.5f, D3DCOLOR_XRGB( 0, 0, 255 )}, // 5
	{  0.5f, -0.5f,-0.5f, D3DCOLOR_XRGB( 0, 0, 255 )}, // 6
	{ -0.5f, -0.5f,-0.5f, D3DCOLOR_XRGB( 255, 0, 0 )} // 7
};
USHORT VIndex[] ={
    0, 1, 2,    // Lado 1
    0, 2, 3,
    4, 5, 6,    // Lado 2
    4, 6, 7,
    3, 2, 5,    // Lado 3
    3, 5, 4,
    2, 1, 6,    // Lado 4
    2, 6, 5,
    1, 7, 6,    // Lado 5
    1, 0, 7,
    0, 3, 4,    // Lado 6
    0, 4, 7,
};


void Juego::Scene2::frame(pGr::Renderer& r ,pGr::Importer& importer, pGr::Game& game, pGr::DirectInput& dInput){
	//input camera.
	float movementSpeed = 0.1f;
	float rotationSpeed = 0.1f;
	//Aceletar//
	if(dInput.keyDown(pGr::Input::KEY_LCONTROL)){
		movementSpeed = 0.9f;
	}
	////////////
	//******Atras y adelante************//
	if(dInput.keyDown(pGr::Input::KEY_W)){
		r.m_pkCamera->walk(movementSpeed);
	}
	if(dInput.keyDown(pGr::Input::KEY_S)){
		r.m_pkCamera->walk(-movementSpeed);
	}
	//******Atras y adelante************//

	//******Girar derecha/izquierda************//
	if(dInput.keyDown(pGr::Input::KEY_D)){
		r.m_pkCamera->roll(rotationSpeed);
	}if(dInput.keyDown(pGr::Input::KEY_A)){
		r.m_pkCamera->roll(-rotationSpeed);
	}
	//******Girar derecha/izquierda************//

	//******Arriba y abajo************//
	if(dInput.keyDown(pGr::Input::KEY_SPACE)){
		r.m_pkCamera->fly(movementSpeed);
	}
	if(dInput.keyDown(pGr::Input::KEY_LSHIFT)){
		r.m_pkCamera->fly(-movementSpeed);
	}
	//******Arriba y abajo************//

	//******Moverse para los costados************//
	if(dInput.keyDown(pGr::Input::KEY_E)){
		r.m_pkCamera->strafe(movementSpeed);
	}
	if(dInput.keyDown(pGr::Input::KEY_Q)){
		r.m_pkCamera->strafe(-movementSpeed);
	}
	//******Moverse para los costados************//
	//OutputDebugString("en el orto");
	r.m_pkCamera->DebugCamPos();
	//theMesh->draw();
	//std::stringstream ss;
	//ss << "Cuberto" << "x: " << theMesh->posX() << "y: " << theMesh->posY() << "z: " << theMesh->posZ() << std::endl;

	//std::string s( ss.str() );

	//OutputDebugString( s.c_str() );
}
bool Juego::Scene2::init(pGr::Renderer& renderer,pGr::Importer& importer){
	
	node = new pGr::Node();
	
	importer.import3DScene("TEST.obj", *node);
	//node->setPos(0,0,0);
   
	return true;
}
bool Juego::Scene2::deInit(){
	return true;
}