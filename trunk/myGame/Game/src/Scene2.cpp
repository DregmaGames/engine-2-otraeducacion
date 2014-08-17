#include "Scene2.h"
using namespace Juego;
void Scene2::frame(pGr::Renderer& r ,pGr::Importer& importer, pGr::Game& game, pGr::DirectInput& dInput){
	static float fSpeed = 1;
	float FPosX = _Sprite->posX();
	float FPosY = _Sprite->posY();
	float FPosZ = _Sprite->posZ();
	static const float scaleX=_Sprite->scaleX();
	//input camera.
	if(dInput.keyDown(pGr::Input::KEY_W)){
		r.m_pkCamera->zoom(1.0f);
	}
	if(dInput.keyDown(pGr::Input::KEY_S)){
		r.m_pkCamera->walk(-5.0f);
	}
	if(dInput.keyDown(pGr::Input::KEY_W)){
		r.m_pkCamera->walk(5.0f);
	}
	if(dInput.keyDown(pGr::Input::KEY_T)){
		r.m_pkCamera->roll(1.0f);
	}if(dInput.keyDown(pGr::Input::KEY_G)){
		r.m_pkCamera->roll(-1.0f);
	}
	if(dInput.keyDown(pGr::Input::KEY_F)){
		r.m_pkCamera->yaw(1.0f);
	}if(dInput.keyDown(pGr::Input::KEY_H)){
		r.m_pkCamera->yaw(-1.0f);
	}
	if(dInput.keyDown(pGr::Input::KEY_Y)){
		r.m_pkCamera->pitch(1.0f);
	}if(dInput.keyDown(pGr::Input::KEY_R)){
		r.m_pkCamera->pitch(-1.0f);
	}
	if(dInput.keyDown(pGr::Input::KEY_SPACE)){
		r.m_pkCamera->fly(1.0f);
	}if(dInput.keyDown(pGr::Input::KEY_D)){
		r.m_pkCamera->strafe(1.0f);
	}
	if(dInput.keyDown(pGr::Input::KEY_A)){
		r.m_pkCamera->strafe(-1.0f);
	}
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