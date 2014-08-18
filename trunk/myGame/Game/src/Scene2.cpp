#include "Scene2.h"
using namespace Juego;
void Scene2::frame(pGr::Renderer& r ,pGr::Importer& importer, pGr::Game& game, pGr::DirectInput& dInput){
	/*if(dInput.keyDown(pGr::Input::KEY_2)){
		game.setCurrentScene("main",importer,"assets/Test.xml");
	}*/

	static float fSpeed = 1;
	float FPosX = _Sprite->posX();
	float FPosY = _Sprite->posY();
	float FPosZ = _Sprite->posZ();
	static const float scaleX=_Sprite->scaleX();
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
	movementSpeed=0.1f;
	//Input Sprite 1
	bool w = false;
	if(dInput.keyDown(pGr::Input::KEY_UP)) {
		FPosY += fSpeed;
		_Sprite->setRotation(D3DXToRadian(+90));
		if(w==false){
			_Sprite->setAnimation("Run");
			w=true;
		}
	}
	if(dInput.keyDown(pGr::Input::KEY_DOWN)) {
		FPosY -= fSpeed;
		_Sprite->setRotation(D3DXToRadian(-90));
		if(w==false){
			_Sprite->setAnimation("Run");
			w=true;
		}
	}
	if(dInput.keyDown(pGr::Input::KEY_RIGHT)) {
		FPosX += fSpeed;
		_Sprite->setRotation(D3DXToRadian(0));
		_Sprite->setScale(scaleX,_Sprite->scaleY());
		if(w==false){
			_Sprite->setAnimation("Run");
			w=true;
		}
	}
	if(dInput.keyDown(pGr::Input::KEY_LEFT)) {
		FPosX -= fSpeed;
		_Sprite->setRotation(D3DXToRadian(0));
		_Sprite->setScale(-scaleX,_Sprite->scaleY());
		if(w==false){
			_Sprite->setAnimation("Run");
			w=true;
		}
	}
	if(w==false){
	_Sprite->setAnimation("Idle");
	}
	_Sprite->setPos(FPosX,FPosY,FPosZ);
	//Colisiones
	for (int i=0;i<m_kObjects.size();i++){
		if(m_kObjects[i]!=NULL){
			if(m_kObjects[i]->getName()!="Link"){
					if(_Sprite->checkCollision(*m_kObjects[i]) == pGr::Entity2D::CollisionHorizontal)
					{
						_Sprite->returnToPos(_Sprite->prevPosX(), _Sprite->posY(), _Sprite->posZ());
					}
					if(_Sprite->checkCollision(*m_kObjects[i]) == pGr::Entity2D::CollisionVertical)
					{
						_Sprite->returnToPos(_Sprite->posX(), _Sprite->prevPosY(), _Sprite->prevPosZ());
					}
			}
		}
	}
}

bool Scene2::init(){
	getEntity(&_Sprite,"Link");
	return true;
}