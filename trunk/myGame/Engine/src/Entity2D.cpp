#pragma once
#define NOMINMAX
#include "Entity2D.h"
#include <Windows.h>
#include <iostream>
#include <d3dx9.h>
#include <iostream>
namespace pGr{
	Entity2D::Entity2D() :
	m_fPosX (0.0f),
	m_fPosY(0.0f),
	m_fRotation(0.0f),
	m_fScaleX(1.0f),
	m_fScaleY(1.0f),
	m_pkTransformationMatrix(new D3DXMATRIX())
	{}

	Entity2D::CollisionResult Entity2D::checkCollision(Entity2D& rkEntity2D) const{
		float fOverlapX = std::max( 0.0f, 
									std::min( m_fPosX + fabs( scaleX() ) / 2.0f,rkEntity2D.posX() + fabs( rkEntity2D.scaleX() ) / 2.0f) -  
									std::max( m_fPosX - fabs( scaleX() ) / 2.0f,rkEntity2D.posX() - fabs( rkEntity2D.scaleX() ) / 2.0f)
		);
		float fOverlapY = std::max( 0.0f,
									std::min( m_fPosY + fabs( scaleY() ) / 2.0f,  rkEntity2D.posY() + fabs( rkEntity2D.scaleY() ) / 2.0f) -  
									std::max( m_fPosY - fabs( scaleY() ) / 2.0f, rkEntity2D.posY() - fabs( rkEntity2D.scaleY() ) / 2.0f)
		);

		if(fOverlapX != 0.0f && fOverlapY != 0.0f){
			if(fOverlapX > fOverlapY){
				return CollisionVertical;
			}else{
				return CollisionHorizontal;
			}
		}
		return NoCollision;
	}
	Entity2D::~Entity2D(){
	
	}
	void Entity2D::setPos (float fPosX,float fPosY, float fPosZ)
	{
		m_fPrevPosX = m_fPosX;
		m_fPrevPosY = m_fPosY;
		m_fPrevPosZ = m_fPosZ; 

		m_fPosX=fPosX;
		m_fPosY=fPosY;
		m_fPosZ=fPosZ;

		updateLocalTransformation();
	}
	void Entity2D::setRotation (float fRotation)
	{
		m_fRotation = fRotation;
		updateLocalTransformation();
	}
	void Entity2D::setScale (float fScaleX,float fScaleY)
	{
		m_fScaleX= fScaleX;
		m_fScaleY= fScaleY;
		updateLocalTransformation();
	}
	void Entity2D::setScale(float fScaleX, float fScaleY, float fScaleZ){
		m_fScaleX= fScaleX;
		m_fScaleY= fScaleY;
		m_fScaleZ= fScaleZ;
		updateLocalTransformation();
	}
	void Entity2D:: updateLocalTransformation ()
	{
		//tranlation matrix
		D3DXMATRIX kTransMat;
		D3DXMatrixTranslation(&kTransMat,m_fPosX,m_fPosY,m_fPosZ);

		//rotacion en z de la matrix
		D3DXMATRIX kRotationMat;
		D3DXMatrixRotationZ(&kRotationMat,m_fRotation);

		D3DXMATRIX kScaleMat;
		D3DXMatrixScaling(&kScaleMat,m_fScaleX,m_fScaleY,m_fScaleZ);

		//build matrix

		D3DXMatrixIdentity(m_pkTransformationMatrix);
		D3DXMatrixMultiply(m_pkTransformationMatrix,&kTransMat,m_pkTransformationMatrix);
		D3DXMatrixMultiply(m_pkTransformationMatrix,&kRotationMat,m_pkTransformationMatrix);
		D3DXMatrixMultiply(m_pkTransformationMatrix,&kScaleMat,m_pkTransformationMatrix);
	}
	const Matrix Entity2D::transformationMatrix(){
		return(m_pkTransformationMatrix);
	}

	float Entity2D::posX(){
		return m_fPosX;
	}

	float Entity2D::posY(){
		return m_fPosY;
	}

	float Entity2D::posZ(){
		return m_fPosZ;
	}

	float Entity2D::scaleX() const{
		return m_fScaleX;
	}

	float Entity2D::scaleY() const{
		return m_fScaleY;
	}
	float Entity2D::scaleZ() const{
		return m_fScaleZ;
	}
	void Entity2D::returnToPos(float fPosX, float fPosY, float fPosZ = 0.0f){
		m_fPosX = fPosX;
		m_fPosY = fPosY;
		m_fPosZ = fPosZ;
	}

	float Entity2D::prevPosX() const{
		return m_fPrevPosX;
	}

	float Entity2D::prevPosY() const{
		return m_fPrevPosY;
	}
	float Entity2D::prevPosZ() const{
		return m_fPrevPosZ;
	}
}