#include "Scene2.h"
using namespace Juego;
void Scene2::frame(pGr::Renderer& r ,pGr::Importer& importer, pGr::Game& game, pGr::DirectInput& dInput){
	static float fSpeed = 1;
	float FPosX = _Sprite->posX();
	float FPosY = _Sprite->posY();
	float FPosZ = _Sprite->posZ();
	static const float scaleX=_Sprite->scaleX();
	//Input Sprite 1
	bool w = false;
	if(dInput.keyDown(pGr::Input::KEY_S)){
		r.m_pkCamera->fly(-1);
	}
	if(dInput.keyDown(pGr::Input::KEY_W)){
		r.m_pkCamera->fly(1);
	}
	if(dInput.keyDown(pGr::Input::KEY_LCONTROL)) {
			D3DXVECTOR3 kPos(0.0f, 0.0f, -1000.0f);
			D3DXVECTOR3 kLook(0.0f, 0.0f, 1.0f);
			D3DXVECTOR3 kUp(0.0f, 1.0f, 0.0f);

			r.setCameraPos(kPos,kLook,kUp);
	}
	if(dInput.keyDown(pGr::Input::KEY_LSHIFT)) {
		D3DXVECTOR3 kPos(0.0f, 0.0f, -500.0f);
			D3DXVECTOR3 kLook(0.0f, 0.0f, 1.0f);
			D3DXVECTOR3 kUp(0.0f, 1.0f, 0.0f);

			r.setCameraPos(kPos,kLook,kUp);
	}
	if(dInput.keyDown(pGr::Input::KEY_UP)) {
		FPosY += fSpeed;
		_Sprite->setRotation(+90);
		if(w==false){
			_Sprite->setAnimation("Run");
			w=true;
		}
	}
	if(dInput.keyDown(pGr::Input::KEY_DOWN)) {
		FPosY -= fSpeed;
		_Sprite->setRotation(-90);
		if(w==false){
			_Sprite->setAnimation("Run");
			w=true;
		}
	}
	if(dInput.keyDown(pGr::Input::KEY_RIGHT)) {
		FPosX += fSpeed;
		_Sprite->setRotation(0);
		_Sprite->setScale(scaleX,_Sprite->scaleY());
		if(w==false){
			_Sprite->setAnimation("Run");
			w=true;
		}
	}
	if(dInput.keyDown(pGr::Input::KEY_LEFT)) {
		FPosX -= fSpeed;
		_Sprite->setRotation(0);
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