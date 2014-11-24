#pragma once
#include "myEngine_API.h"
#include "Mathjavi.h"

class hkpRigidBody;
namespace pGr{
	class Collider;
	class MYENGINE_API RigidBody{
		friend class Physics;

	public:
		RigidBody();
		virtual ~RigidBody();

		void setPosition(float,float,float);
		float posX() const;
		float posY() const;
		float posZ() const;

		void setRotation(float,float,float);
		float rotationX () const;
		float rotationY () const;
		float rotationZ () const;

		const Matrix& transform () const { return m_pTransformation; };
	
		void setCollider(Collider*);
		const Collider* collider() const { return m_pkCollider; };

		enum HavokMotion{
			Static,
			Dynamic,
			HavokMotionCount
		};

		void setHavokMotion(HavokMotion type);
		HavokMotion havokMotion () const { return m_HMotion; };

	private:
		Matrix m_pTransformation;
		Collider* m_pkCollider;
		HavokMotion m_HMotion;

	protected:

		hkpRigidBody* rigidbody(){ return m_pkRigidBody; }
		hkpRigidBody* m_pkRigidBody;
	};
}