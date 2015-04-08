#pragma once
#define NOMINMAX

#include "Entity3D.h"

#include "Mesh.h"
#include "Node.h"
#include <d3dx9.h>
#include <iostream>
#include <Windows.h>

using namespace pGr;
Entity3D::Entity3D() :
m_fPosX(0.0f),
m_fPosY(0.0f),
m_fPosZ(0.0f),
m_fRotX(0.0f),
m_fRotY(0.0f),
m_fRotZ(0.0f),
m_fScaleX(1.0f),
m_fScaleY(1.0f),
m_fScaleZ(1.0f),
m_pkTransformationMatrix(new D3DXMATRIX()),
m_pkTransformationLocalMatrix(new D3DXMATRIX()),
m_pkParent(NULL),
m_pkAABB(new AABB())
{
	D3DXMatrixIdentity(m_pkTransformationMatrix);
	updateLocalTransformation();
}
Entity3D::~Entity3D()
{
	delete m_pkTransformationMatrix;
	m_pkTransformationMatrix = NULL;

	delete m_pkTransformationLocalMatrix;
	m_pkTransformationLocalMatrix = NULL;
}

void Entity3D::setRotationX(float fRotX){
	m_fRotX = fRotX;
	updateLocalTransformation();
}
void Entity3D::setRotationY(float fRotY){
	m_fRotX = fRotY;
	updateLocalTransformation();
}
void Entity3D::setRotationZ(float fRotZ){
	m_fRotX = fRotZ;
	updateLocalTransformation();
}

void Entity3D::setPositionX(float fPosX){
	m_fPosX = fPosX;
	updateLocalTransformation();
}
void Entity3D::setPositionY(float fPosY){
	m_fPosY = fPosY;
	updateLocalTransformation();
}
void Entity3D::setPositionZ(float fPosZ){
	m_fPosX = fPosZ;
	updateLocalTransformation();
}

void Entity3D::setPosition(float fPosX, float fPosY, float fPosZ){
	m_fPosX = fPosX;
	m_fPosY = fPosY;
	m_fPosZ = fPosZ;
	updateLocalTransformation();
}

void Entity3D::setRotation(float fRotX, float fRotY, float fRotZ)
{
	m_fRotX = fRotX;
	m_fRotY = fRotY;
	m_fRotZ = fRotZ;
	updateLocalTransformation();
}

void Entity3D::setScale(float fScaleX, float fScaleY, float fScaleZ)
{
	m_fScaleX = fScaleX;
	m_fScaleY = fScaleY;
	m_fScaleZ = fScaleZ;
	updateLocalTransformation();
}

void Entity3D::updateLocalTransformation()
{
	//tranlation matrix
	D3DXMATRIX kTransMat;
	D3DXMatrixTranslation(&kTransMat, m_fPosX, m_fPosY, m_fPosZ);

	//rotacion en z de la matrix
	D3DXMATRIX rotationMatrixX, rotationMatrixY, rotationMatrixZ;
	D3DXMatrixRotationZ(&rotationMatrixX, m_fRotX);
	D3DXMatrixRotationZ(&rotationMatrixY, m_fRotY);
	D3DXMatrixRotationZ(&rotationMatrixZ, m_fRotZ);

	D3DXMATRIX kScaleMat;
	D3DXMatrixScaling(&kScaleMat, m_fScaleX, m_fScaleY, m_fScaleZ);

	//build matrix
	D3DXMatrixIdentity(m_pkTransformationLocalMatrix);
	D3DXMatrixMultiply(m_pkTransformationLocalMatrix, &kTransMat, m_pkTransformationMatrix);
	D3DXMatrixMultiply(m_pkTransformationLocalMatrix, &kTransMat, &rotationMatrixZ);
	D3DXMatrixMultiply(m_pkTransformationLocalMatrix, &kTransMat, &rotationMatrixY);
	D3DXMatrixMultiply(m_pkTransformationLocalMatrix, &kTransMat, &rotationMatrixX);
	D3DXMatrixMultiply(m_pkTransformationLocalMatrix, &kScaleMat, m_pkTransformationMatrix);
}

const Matrix Entity3D::transformationMatrix()
{
	return(m_pkTransformationMatrix);
}

void Entity3D::setParent(Node* pkParent)
{
	m_pkParent = pkParent;
}

void Entity3D::updateTransformation()
{
	updateLocalTransformation();
	if (m_pkParent){
		D3DXMatrixIdentity(m_pkTransformationMatrix);
		D3DXMatrixMultiply(m_pkTransformationMatrix, m_pkParent->m_pkTransformationMatrix, m_pkTransformationLocalMatrix);
	}
	else
		(*m_pkTransformationMatrix) = (*m_pkTransformationLocalMatrix);
}
const AABB&	Entity3D::getAABB() const{ return *m_pkAABB; }
AABB&		Entity3D::getAABB()	  { return *m_pkAABB; }