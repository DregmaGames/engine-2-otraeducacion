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
	m_pkAABB(new AABB()),
	m_pkRigidBody(new RigidBody())
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

		delete m_pkRigidBody,
		m_pkRigidBody = NULL;
	}

	void Entity3D::setPositionX(float fPosX)
	{
		m_pkRigidBody->setPosition(fPosX, m_pkRigidBody->getPosY(), m_pkRigidBody->getPosZ());
		std::cout << "posX: " << m_pkRigidBody->getPosX() << std::endl;
		updateLocalTransformation();
	}
	void Entity3D::setPositionY(float fPosY)
	{
		m_pkRigidBody->setPosition(m_pkRigidBody->getPosX(), fPosY, m_pkRigidBody->getPosZ());
		std::cout << "posY: " << m_pkRigidBody->getPosY() << std::endl;
		updateLocalTransformation();
	}
	void Entity3D::setPositionZ(float fPosZ)
	{
		m_pkRigidBody->setPosition(m_pkRigidBody->getPosX(), m_pkRigidBody->getPosY(), fPosZ);
		std::cout << "posZ: " << m_pkRigidBody->getPosZ() << std::endl;
		updateLocalTransformation();
	}

	void Entity3D::setRotationX(float fRotationX)
	{
		m_pkRigidBody->setRotation(fRotationX, m_pkRigidBody->getRotationY(), m_pkRigidBody->getRotationZ());
		std::cout << "rotX: " << m_pkRigidBody->getRotationX() << std::endl;
		updateLocalTransformation();
	}
	void Entity3D::setRotationY(float fRotationY)
	{
		m_pkRigidBody->setRotation(m_pkRigidBody->getRotationX(), fRotationY, m_pkRigidBody->getRotationZ());
		std::cout << "rotY: " << m_pkRigidBody->getRotationY() << std::endl;
		updateLocalTransformation();
	}
	void Entity3D::setRotationZ(float fRotationZ)
	{
		m_pkRigidBody->setRotation(m_pkRigidBody->getRotationX(), m_pkRigidBody->getRotationY(), fRotationZ);
		std::cout << "rotZ: " << m_pkRigidBody->getRotationZ() << std::endl;
		updateLocalTransformation();
	}

	void Entity3D::setPosition (float fPosX,float fPosY, float fPosZ)
	{
		m_pkRigidBody->setPosition(fPosX, fPosY, fPosZ);
		std::cout << "PosX: " << m_pkRigidBody->getPosX() << std::endl;
		updateLocalTransformation();
	}

	void Entity3D::setRotation (float fRotX, float fRotY, float fRotZ)
	{
		m_pkRigidBody->setRotation(fRotX, fRotY, fRotZ);
		updateLocalTransformation();
	}

	void Entity3D::setScale(float fScaleX, float fScaleY, float fScaleZ)
	{
		m_fScaleX= fScaleX;
		m_fScaleY= fScaleY;
		m_fScaleZ= fScaleZ;
		updateLocalTransformation();
	}

	void Entity3D::updateLocalTransformation ()
	{
		//tranlation matrix
		D3DXMATRIX kTransMat;
		D3DXMatrixTranslation(&kTransMat, getPosX(), getPosY(), getPosZ());

		//rotacion en z de la matrix
		D3DXMATRIX rotationMatrixX, rotationMatrixY, rotationMatrixZ;
		D3DXMatrixRotationX(&rotationMatrixX, getRotationX());
		D3DXMatrixRotationY(&rotationMatrixY, getRotationY());
		D3DXMatrixRotationZ(&rotationMatrixZ, getRotationZ());

		D3DXMATRIX kScaleMat;
		D3DXMatrixScaling(&kScaleMat, m_fScaleX, m_fScaleY, m_fScaleZ);

		//build matrix
		D3DXMatrixIdentity(m_pkTransformationLocalMatrix);
		//************
		D3DXMatrixMultiply(m_pkTransformationLocalMatrix,m_pkTransformationLocalMatrix,&kTransMat);
		D3DXMatrixMultiply(m_pkTransformationLocalMatrix,m_pkTransformationLocalMatrix,&rotationMatrixX);
		D3DXMatrixMultiply(m_pkTransformationLocalMatrix,m_pkTransformationLocalMatrix,&rotationMatrixY);
		D3DXMatrixMultiply(m_pkTransformationLocalMatrix,m_pkTransformationLocalMatrix,&rotationMatrixZ);
		D3DXMatrixMultiply(m_pkTransformationLocalMatrix, m_pkTransformationLocalMatrix, &kScaleMat);
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
		if(m_pkParent){
			D3DXMatrixIdentity(m_pkTransformationMatrix);
			D3DXMatrixMultiply(m_pkTransformationMatrix,m_pkParent ->m_pkTransformationMatrix , m_pkTransformationLocalMatrix);
		}
		else
		(*m_pkTransformationMatrix) = (*m_pkTransformationLocalMatrix);
	}
	const AABB&	Entity3D::getAABB() const{ return *m_pkAABB; }
	AABB&		Entity3D::getAABB()	  { return *m_pkAABB; }