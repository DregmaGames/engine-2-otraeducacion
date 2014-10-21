#include "Scene2.h"
#include<sstream>
#include<string>
pGr::ColorVertex VBuffer[] = {
{-0.5f, 0.5f, -0.5f, D3DCOLOR_XRGB( 255, 0, 0 )}, // 0 
{0.5f, 0.5f, -0.5f, D3DCOLOR_XRGB( 0, 255, 0 )}, // 1 
{ 0.5f, 0.5f, 0.5f, D3DCOLOR_XRGB( 40, 0, 120 )}, // 2 
{ -0.5f, 0.5f, 0.5f, D3DCOLOR_XRGB( 255, 0, 0 )}, // 3

{ -0.5f, -0.5f, 0.5f, D3DCOLOR_XRGB( 0, 255, 0 )}, // 4
{  0.5f, -0.5f, 0.5f, D3DCOLOR_XRGB( 40, 0, 120 )}, // 5
{  0.5f, -0.5f,-0.5f, D3DCOLOR_XRGB( 255, 0, 0 )}, // 6
{ -0.5f, -0.5f,-0.5f, D3DCOLOR_XRGB( 0, 255, 0 )} // 7
};
USHORT VIndex[] ={
    0, 1, 2,    // Lado 1
    2, 1, 3,
    4, 0, 6,    // Lado 2
    6, 0, 2,
    7, 5, 6,    // Lado 3
    6, 5, 4,
    3, 1, 7,    // Lado 4
    7, 1, 5,
    4, 5, 0,    // Lado 5
    0, 5, 1,
    3, 7, 2,    // Lado 6
    2, 7, 6,
};

using namespace Juego;
void Scene2::frame(pGr::Renderer& r ,pGr::Importer& importer, pGr::Game& game, pGr::DirectInput& dInput){
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
	theMesh->draw(r);
	std::stringstream ss;
	ss << "Cuberto" << "x: " << theMesh->posX() << "y: " << theMesh->posY() << "z: " << theMesh->posZ() << std::endl;

	std::string s( ss.str() );

	OutputDebugString( s.c_str() );
}
bool Scene2::init(pGr::Renderer& r,pGr::Importer& i){
	theMesh = new pGr::Mesh(r);
	 theMesh->setData(VBuffer,8,pGr::Primitive::TriangleList,VIndex,36);
        theMesh->setPos(0,0,0);
        theMesh->setScale(10,10,10);
	return true;
}
bool Scene2::deInit(){
	return true;
}