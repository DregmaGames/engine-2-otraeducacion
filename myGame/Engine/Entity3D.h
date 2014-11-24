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

	class MYENGINE_API Entity3D
	{
		friend class Node;
		public:

			Entity3D();
			virtual ~Entity3D();

			enum CollisionResult
			{
				CollisionVertical,
				CollisionHorizontal,
				NoCollision
			};

			float getPosX(){ return m_pkRigidBody->posX(); }
			float getPosY(){ return m_pkRigidBody->posY(); }
			float getPosZ(){ return m_pkRigidBody->posZ(); }
			float getRotationX() const { return m_pkRigidBody->rotationX(); }
			float getRotationY() const { return m_pkRigidBody->rotationY(); }
			float getRotationZ() const { return m_pkRigidBody->rotationZ(); }
			float getScaleX () const{ return m_fScaleX;}
			float getScaleY () const{ return m_fScaleY;}
			float getScaleZ () const{ return m_fScaleZ;}

			AABB& aabb();
			bool m_Coll;//si es o no colisionable.
			std::string m_Name;	//nombre del objeto

			const AABB& aabb() const;
			const Matrix transformationMatrix();
			
			void setParent (Node* pkParent);
			void setColl(bool col){m_Coll = col;}
			void setName(std::string name){m_Name = name;}
			void setPos(float fPosX,float fPosY,float fPosZ);
			void setScale(float m_fScaleX,float m_fScaleY, float m_fScaleZ);
			void setRotation(float fRotationX, float fRotationY, float fRotationZ);

			void updateLocalTransformation();
			void drawAABB(Renderer& pkRenderer) const;
		
			virtual void draw() = 0;
			virtual void updateTransformation();
		
			CollisionResult checkCollision(Entity3D& rkEntity3D) const;

			std::string getName(){return m_Name;}

		protected:
			Matrix m_pkTransformationMatrix;
			Matrix m_pkTransformationLocalMatrix;

		private:

			AABB* m_kAABB;
			Node* m_pkParent;
			RigidBody* m_pkRigidBody;

			float m_fPosX, m_fPosY, m_fPosZ;
			float m_fRotX, m_fRotY, m_fRotZ;
			float m_fScaleX,m_fScaleY, m_fScaleZ;
	};
}
#endif 