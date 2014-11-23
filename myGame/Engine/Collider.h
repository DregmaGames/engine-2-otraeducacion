#pragma once
#include "../myEngine_API.h"
#include "Physics.h"
namespace pGr{
	class Mesh;
}

	class hkpRigidBody;
	class hkpShape;
	class hkpBoxShape;
	class hkpConvexVerticesShape;

namespace pGr{
	class MYENGINE_API Collider{
	friend class Physics;
	friend class RigidBody;
	
	public:
		Collider();
		virtual ~Collider();

		virtual void calculate(const Mesh* pkMesh) = 0;
		void setPosition (float fX, float fY, float fZ);

	protected:
		virtual hkpShape* shape () = 0;
		hkpRigidBody* rigidBody();
		hkpRigidBody* m_pkRigidBody;
	};

	class MYENGINE_API BoxCollider : public Collider{
		public:
			BoxCollider();
			~BoxCollider();
			void calculate(const Mesh* pkMesh);

		protected:
			hkpShape* shape();

		private:
			hkpBoxShape* m_pkBox;
	};

	class MYENGINE_API MeshCollider : public Collider{
		public:
			MeshCollider();
			~MeshCollider();
			void calculate(const Mesh* pkMesh);
		protected:
			hkpShape* shape();
		private:
			hkpConvexVerticesShape* m_pkMeshCollider;
	};

}