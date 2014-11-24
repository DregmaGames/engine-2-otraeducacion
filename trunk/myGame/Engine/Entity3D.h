#ifndef ENTITY3D_H
#define ENTITY3D_H

#include "AABB.h"
#include "mathjavi.h"
#include "Renderer.h"
#include "RenderTypes.h"
#include "myengine_api.h"
#include "RigidBody.h"
#include <string>

namespace pGr{

	class Node;
	class Timer;
	class Renderer;
	class Rigidbody;
	class MYENGINE_API Entity3D
	{
		friend class Node;
		public:

			Entity3D();
			virtual ~Entity3D();

			float getScaleX () const{ return m_fScaleX;}
			float getScaleY () const{ return m_fScaleY;}
			float getScaleZ () const{ return m_fScaleZ;}
			float getPosX(){ return m_pkRigidBody->posX(); }
			float getPosY(){ return m_pkRigidBody->posY(); }
			float getPosZ(){ return m_pkRigidBody->posZ(); }
			float getRotationX() const { return m_pkRigidBody->rotationX(); }
			float getRotationY() const { return m_pkRigidBody->rotationY(); }
			float getRotationZ() const { return m_pkRigidBody->rotationZ(); }

			RigidBody* getRigidBody() const{ return m_pkRigidBody; }

			std::string m_Name;	//nombre del objeto

			const Matrix transformationMatrix();
			
			std::string getName(){return m_Name;}
			void setName(std::string name){m_Name = name;}

			void setPos(float fPosX,float fPosY,float fPosZ);
			void setScale(float m_fScaleX,float m_fScaleY, float m_fScaleZ);
			void setRotation(float fRotationX, float fRotationY, float fRotationZ);
			
			virtual void draw() = 0;
			void updateLocalTransformation();
			virtual void updateTransformation();
		
		protected:

			Matrix m_pkTransformationMatrix;
			Matrix m_pkTransformationLocalMatrix;

		private:

			Node* m_pkParent;
			RigidBody* m_pkRigidBody;

			void setParent (Node* pkParent);
			float m_fScaleX,m_fScaleY, m_fScaleZ;
	};
}
#endif 