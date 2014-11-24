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
	m_fPosX (0.0f),
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
	m_kAABB(new AABB()),
	m_pkRigidBody(new RigidBody()),
	m_pkParent(NULL)
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

		delete m_kAABB;
		m_kAABB = NULL;

		delete m_pkRigidBody,
		m_pkRigidBody = NULL;
	}

	void Entity3D::setPos (float fPosX,float fPosY, float fPosZ)
	{
		m_pkRigidBody->setPosition(fPosX, fPosY, fPosZ);
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
		//updateLocalTransformation();
	}

	void Entity3D::updateLocalTransformation ()
	{
		//tranlation matrix
		D3DXMATRIX kTransMat;
		D3DXMatrixTranslation(&kTransMat, m_pkRigidBody->posX(), m_pkRigidBody->posY(), m_pkRigidBody->posZ());

		//rotacion en z de la matrix
		D3DXMATRIX rotationMatrixX, rotationMatrixY, rotationMatrixZ;
		D3DXMatrixRotationZ(&rotationMatrixX, m_pkRigidBody->rotationX());
		D3DXMatrixRotationZ(&rotationMatrixY, m_pkRigidBody->rotationY());
		D3DXMatrixRotationZ(&rotationMatrixZ, m_pkRigidBody->rotationZ());

		D3DXMATRIX kScaleMat;
		D3DXMatrixScaling(&kScaleMat, m_fScaleX, m_fScaleY, m_fScaleZ);

		//build matrix
		D3DXMatrixIdentity(m_pkTransformationLocalMatrix);
		D3DXMatrixMultiply(m_pkTransformationLocalMatrix,&kTransMat,m_pkTransformationMatrix);
		D3DXMatrixMultiply(m_pkTransformationLocalMatrix,&kTransMat,&rotationMatrixZ);
		D3DXMatrixMultiply(m_pkTransformationLocalMatrix,&kTransMat,&rotationMatrixY);
		D3DXMatrixMultiply(m_pkTransformationLocalMatrix,&kTransMat,&rotationMatrixX);
		D3DXMatrixMultiply(m_pkTransformationLocalMatrix,&kScaleMat,m_pkTransformationMatrix);
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
		if(m_pkParent)
		{
			D3DXMatrixIdentity(m_pkTransformationMatrix);
			D3DXMatrixMultiply(m_pkTransformationMatrix, m_pkParent->m_pkTransformationMatrix, m_pkTransformationLocalMatrix);
		}else
		{
			(*m_pkTransformationMatrix) = (*m_pkTransformationLocalMatrix);
		}
	}


	void Entity3D::drawAABB(Renderer& pkRenderer) const
	{
		/*static Mesh* s_AKAABBMesh;
		static bool s_bIsInitialized = false;

		if(!s_bIsInitialized)
		{
			s_bIsInitialized = true;
			s_AKAABBMesh = new Mesh(pkRenderer);
			MeshVertex * pakVertices = new MeshVertex[8];
			unsigned short* pausIndices = new unsigned short[24];

			pakVertices[0].x = +0.5f;       pakVertices[0].y = +0.5f;       pakVertices[0].z = +0.5f;
			pakVertices[1].x = +0.5f;       pakVertices[1].y = +0.5f;       pakVertices[1].z = -0.5f;
			pakVertices[2].x = +0.5f;       pakVertices[2].y = -0.5f;       pakVertices[2].z = +0.5f;
			pakVertices[3].x = +0.5f;       pakVertices[3].y = -0.5f;       pakVertices[3].z = -0.5f;
			pakVertices[4].x = -0.5f;       pakVertices[4].y = +0.5f;       pakVertices[4].z = +0.5f;
			pakVertices[5].x = -0.5f;       pakVertices[5].y = +0.5f;       pakVertices[5].z = -0.5f;
			pakVertices[6].x = -0.5f;       pakVertices[6].y = -0.5f;       pakVertices[6].z = +0.5f;
			pakVertices[7].x = -0.5f;       pakVertices[7].y = -0.5f;       pakVertices[7].z = -0.5f;

			pausIndices[0] =	0;			pausIndices[1] =	1;			pausIndices[2] =	1;		pausIndices[3] = 3;
			pausIndices[4] =	3;			pausIndices[5] =	2;			pausIndices[6] =	2;		pausIndices[7] = 0;
			pausIndices[8] =	4;			pausIndices[9] =	5;			pausIndices[10] =	5;		pausIndices[11] = 7;
			pausIndices[12] =	7;			pausIndices[13] =	6;			pausIndices[14] =	6;		pausIndices[15] = 4;
			pausIndices[16] =	0;			pausIndices[17] =	4;			pausIndices[18] =	1;		pausIndices[19] = 5;
			pausIndices[20] =	3;			pausIndices[21] =	7;			pausIndices[22] =	2;		pausIndices[23] = 6;

			s_AKAABBMesh->setData(pakVertices,8,LineStrip,pausIndices,24);

			delete[] pakVertices;
			delete[] pausIndices;
		}

		s_AKAABBMesh->setPos((m_pkTransformationMatrix->_41 + m_pkTransformationLocalMatrix->_41) / aabb().width() + aabb().offset()->x / aabb().width()  ,
							 (m_pkTransformationMatrix->_42 + m_pkTransformationLocalMatrix->_42) / aabb().width() + aabb().offset()->y / aabb().height() , 
							 (m_pkTransformationMatrix->_43 + m_pkTransformationLocalMatrix->_43) / aabb().width() + aabb().offset()->z / aabb().depth()  );
						  
	

		s_AKAABBMesh->setScale(aabb().width(), aabb().height(), aabb().depth() );
		s_AKAABBMesh->updateTransformation();
		s_AKAABBMesh->draw();*/

	}

	const AABB&	Entity3D::aabb() const{
		return *m_kAABB; 
	}
	AABB& Entity3D::aabb(){
		return *m_kAABB; 
	}


