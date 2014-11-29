#ifndef ENTITY3D_H
#define ENTITY3D_H

#include "AABB.h"
#include "mathjavi.h"
#include "Renderer.h"
#include "RenderTypes.h"
#include "myengine_api.h"
#include "RigidBody.h"
#include "AABB.h"
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

			float getScaleX () const{ return m_fScaleX;}
			float getScaleY () const{ return m_fScaleY;}
			float getScaleZ () const{ return m_fScaleZ;}
			float getPosX(){ return m_pkRigidBody->getPosX(); }
			float getPosY(){ return m_pkRigidBody->getPosY(); }
			float getPosZ(){ return m_pkRigidBody->getPosZ(); }
			float getRotationX() const { return m_pkRigidBody->getRotationX(); }
			float getRotationY() const { return m_pkRigidBody->getRotationY(); }
			float getRotationZ() const { return m_pkRigidBody->getRotationZ(); }

			RigidBody* getRigidBody() const{ return m_pkRigidBody; }

			std::string m_Name;	//nombre del objeto

			const Matrix transformationMatrix();
			
			std::string getName(){return m_Name;}
			void setName(std::string name){m_Name = name;}

			void setScale(float m_fScaleX,float m_fScaleY, float m_fScaleZ);

			void setPosition(float fPosX,float fPosY,float fPosZ);
			void setPositionX(float fPosX);
			void setPositionY(float fPosY);
			void setPositionZ(float fPosZ);


			void setRotation(float fRotationX,float fRotationY,float fRotationZ);
			void setRotationX(float fRotationX);
			void setRotationY(float fRotationY);
			void setRotationZ(float fRotationZ);
			
			virtual void draw() = 0;
			void updateLocalTransformation();
			virtual void updateTransformation();
			void setParent (Node* pkParent);

			const AABB& getAABB() const;
			AABB& getAABB();

		protected:

			Matrix m_pkTransformationMatrix;
			Matrix m_pkTransformationLocalMatrix;

		private:

			AABB* m_pkAABB;
			Node* m_pkParent;
			RigidBody* m_pkRigidBody;

			
			float m_fScaleX,m_fScaleY, m_fScaleZ;
	};
}
#endif 