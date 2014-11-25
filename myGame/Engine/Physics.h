#pragma once
#include "myEngine_API.h"

class hkVisualDebugger;
class hkpPhysicsContext;
class hkpWorld;
class hkpRigidBody;

namespace pGr{
	class RigidBody;

	class MYENGINE_API Physics{

		friend class Engine;

	protected:
		Physics();
		~Physics();
	public:
		void update(float fk_DeltaTime);

		static Physics* getInstance();
		static void addEntity(RigidBody* pkR); 
	private:
		static Physics* Instance;
		static void HavokFailure(const char* msg, void* userAgent);
		static void StartTestScene();
		static hkVisualDebugger* m_VDebugger;
		static hkpPhysicsContext* m_HContext;

		static hkpWorld* m_HWorld;
		static bool HavokStarted;

		static hkpRigidBody* m_RBody1;
	};
}