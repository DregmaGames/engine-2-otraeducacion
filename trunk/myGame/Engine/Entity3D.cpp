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
	m_fScaleX(1.0f),
	m_fScaleY(1.0f),
	m_fScaleZ(1.0f),
	m_pkTransformationMatrix(new D3DXMATRIX()),
	m_pkTransformationLocalMatrix(new D3DXMATRIX()),
	m_pkParent(NULL),
	m_pkRigidBody(new RigidBody()){
		updateLocalTransformation();
	}

	Entity3D::~Entity3D()
	{
		delete m_pkTransformationMatrix;
		m_pkTransformationMatrix = NULL;

		delete m_pkTransformationLocalMatrix;
		m_pkTransformationLocalMatrix = NULL;

		delete m_pkRigidBody,
		m_pkRigidBody = NULL;
	}

	void Entity3D::setPos (float fPosX,float fPosY, float fPosZ)
	{
		m_pkRigidBody->setPosition(fPosX, fPosY, fPosZ);
		
	}

	void Entity3D::setRotation (float fRotX, float fRotY, float fRotZ)
	{
		m_pkRigidBody->setRotation(fRotX, fRotY, fRotZ);
		
	}

	void Entity3D::setScale(float fScaleX, float fScaleY, float fScaleZ)
	{
		m_fScaleX= fScaleX;
		m_fScaleY= fScaleY;
		m_fScaleZ= fScaleZ;
	}

	void Entity3D::updateLocalTransformation ()
	{
		//tranlation matrix
		D3DXMATRIX kTransMat;
		D3DXMatrixTranslation(&kTransMat, getPosX(), getPosY(), getPosZ());

		//rotacion en z de la matrix
		D3DXMATRIX rotationMatrixX, rotationMatrixY, rotationMatrixZ;
		D3DXMatrixRotationZ(&rotationMatrixX, getRotationX());
		D3DXMatrixRotationZ(&rotationMatrixY, getRotationY());
		D3DXMatrixRotationZ(&rotationMatrixZ, getRotationZ());

		D3DXMATRIX kScaleMat;
		D3DXMatrixScaling(&kScaleMat, m_fScaleX, m_fScaleY, m_fScaleZ);

		//build matrix
		D3DXMatrixIdentity(m_pkTransformationLocalMatrix);
		D3DXMatrixMultiply(m_pkTransformationLocalMatrix,m_pkTransformationLocalMatrix,&kTransMat);
		D3DXMatrixMultiply(m_pkTransformationLocalMatrix,m_pkTransformationLocalMatrix,&rotationMatrixX);
		D3DXMatrixMultiply(m_pkTransformationLocalMatrix,m_pkTransformationLocalMatrix,&rotationMatrixY);
		D3DXMatrixMultiply(m_pkTransformationLocalMatrix,m_pkTransformationLocalMatrix,&rotationMatrixZ);
		D3DXMatrixMultiply(m_pkTransformationLocalMatrix,m_pkTransformationLocalMatrix,&kScaleMat);
	}

	const Matrix Entity3D::transformationMatrix()
	{
		return(m_pkTransformationMatrix);
	}

	void Entity3D::setParent (Node* pkParent)
	{
		m_pkParent = pkParent;
	}

	void Entity3D::updateTransformation()
	{
		updateLocalTransformation();
		(*m_pkTransformationMatrix) = (*m_pkTransformationLocalMatrix);
	}

	void Entity3D::setPosX(float fPosX)
	{
		m_pkRigidBody->setPosition(fPosX, m_pkRigidBody->getPosY(),m_pkRigidBody->getPosZ());
	}
	void Entity3D::setPosY(float fPosY)
	{
		m_pkRigidBody->setPosition(m_pkRigidBody->getPosX(), fPosY,m_pkRigidBody->getPosZ());
	}
	void Entity3D::setPosZ(float fPosZ)
	{
		m_pkRigidBody->setPosition(m_pkRigidBody->getPosX(), m_pkRigidBody->getPosY(),fPosZ);
	}

	void Entity3D::setRotationX(float fRotationX)
	{
		m_pkRigidBody->setPosition(fRotationX, m_pkRigidBody->getRotationY(),m_pkRigidBody->getRotationZ());
	}
	void Entity3D::setRotationY(float fRotationY)
	{
		m_pkRigidBody->setPosition(m_pkRigidBody->getRotationX(), fRotationY,m_pkRigidBody->getRotationZ());
	}
	void Entity3D::setRotationZ(float fRotationZ)
	{
		m_pkRigidBody->setPosition(m_pkRigidBody->getRotationX(), m_pkRigidBody->getRotationY(),fRotationZ);
	}

