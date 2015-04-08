#ifndef ENTITY3D_H
#define ENTITY3D_H

#include "AABB.h"
#include "mathjavi.h"
#include "Renderer.h"
#include "RenderTypes.h"
#include "myengine_api.h"
#include <string>

namespace pGr{

	class Node;
	class Timer;
	class Renderer;
	class Rigidbody;
	class AABB;
	class MYENGINE_API Entity3D
	{
		friend class Node;
	public:

		Entity3D();
		virtual ~Entity3D();

		float getScaleX() const{ return m_fScaleX; }
		float getScaleY() const{ return m_fScaleY; }
		float getScaleZ() const{ return m_fScaleZ; }
		float getPosX(){ return m_fPosX; }
		float getPosY(){ return m_fPosY; }
		float getPosZ(){ return m_fPosZ; }
		float getRotationX() const { return m_fRotX; }
		float getRotationY() const { return m_fRotY; }
		float getRotationZ() const { return m_fRotZ; }

		std::string m_Name;	//nombre del objeto

		const Matrix transformationMatrix();

		std::string getName(){ return m_Name; }
		void setName(std::string name){ m_Name = name; }


		

		//seters
		//scale
		void setScale(float m_fScaleX, float m_fScaleY, float m_fScaleZ);
		//pos
		void setPosition(float m_fPosX, float m_fPosY, float m_fPosZ);
		void setPositionX(float m_fPosX);
		void setPositionY(float m_fPosY);
		void setPositionZ(float m_fPosZ);
		//rot
		void setRotation(float fRotationX, float fRotationY, float fRotationZ);
		void setRotationX(float fRotationX);
		void setRotationY(float fRotationY);
		void setRotationZ(float fRotationZ);
		//------

		virtual void draw() = 0;
		void updateLocalTransformation();
		virtual void updateTransformation();
		void setParent(Node* pkParent);

		const AABB& getAABB() const;
		AABB& getAABB();

	protected:

		Matrix m_pkTransformationMatrix;
		Matrix m_pkTransformationLocalMatrix;

	private:

		AABB* m_pkAABB;
		Node* m_pkParent;

		float m_fPosX, m_fPosY, m_fPosZ;
		float m_fRotX, m_fRotY, m_fRotZ;
		float m_fScaleX, m_fScaleY, m_fScaleZ;
	};
}
#endif 