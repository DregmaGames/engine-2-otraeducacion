#include "Physics.h"
#include "RigidBody.h"
#include <iostream>

#pragma comment (lib, "hkBase.lib")
#pragma comment (lib, "hkVisualize.lib")
#pragma comment (lib, "hkInternal.lib")
#pragma comment (lib, "hkSerialize.lib")
#pragma comment (lib, "hkGeometryUtilities.lib")
#pragma comment (lib, "hkcdInternal.lib")
#pragma comment (lib, "hkcdCollide.lib")
#pragma comment (lib, "hkpCollide.lib")
#pragma comment (lib, "hkpConstraint.lib")
#pragma comment (lib, "hkpConstraintSolver.lib")
#pragma comment (lib, "hkpDynamics.lib")
#pragma comment (lib, "hkpInternal.lib")
#pragma comment (lib, "hkpUtilities.lib")

#include <xmmintrin.h>
#include <Common/Base/hkBase.h>
#include <Physics2012/Dynamics/World/hkpWorld.h>
#include <Common/Visualize/hkVisualDebugger.h>
#include <Physics2012/Utilities/VisualDebugger/hkpPhysicsContext.h>
#include <Common/Base/Memory/System/Util/hkMemoryInitUtil.h>
#include <Common/Base/Memory/Allocator/Malloc/hkMallocAllocator.h>
#include <Physics2012/Collide/Dispatch/hkpAgentRegisterUtil.h>

#include <Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Physics2012/Collide/Shape/Convex/Box/hkpBoxShape.h>
#include <Physics2012/Collide/Shape/Convex/Sphere/hkpSphereShape.h>
#include <Physics2012/Utilities/Dynamics/Inertia/hkpInertiaTensorComputer.h>
#include <Physics2012/Collide/Shape/Convex/hkpConvexShape.h>
#include <Physics2012/Collide/Shape/Convex/ConvexVertices/hkpConvexVerticesShape.h>
#include <Common/Internal/ConvexHull/hkGeometryUtility.h>

using namespace pGr;

hkVisualDebugger* Physics::m_VDebugger = NULL;
hkpPhysicsContext* Physics::m_HContext = NULL;

hkpWorld* Physics::m_HWorld = NULL;

bool Physics::HavokStarted = false;
//*************************************************************
hkpRigidBody* Physics::m_RBody1 = NULL;
Physics*	  Physics::Instance		= NULL;
//**************************************************************
Physics::Physics ()
{
	if(!HavokStarted) {
		#if defined(HK_COMPILER_HAS_INTRINSICS_IA32) && (HK_CONFIG_SIMD ==  HK_CONFIG_SIMD_ENABLED)
			_MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
		#endif

		//Havok con Memory Leak Detector
		hkMemoryRouter* memoryRouter = hkMemoryInitUtil::initChecking( hkMallocAllocator::m_defaultMallocAllocator,  hkMemorySystem::FrameInfo(1024 * 1024));
		hkBaseSystem::init(memoryRouter, HavokFailure);
		//------------------------------


		//------------WORLD CONFIG-------------
			//Physics-----
			hkpWorldCinfo HavokWorldInfo;
			HavokWorldInfo.m_gravity = hkVector4(0.0f, -9.8f, 0.0f);//Gravity
			HavokWorldInfo.m_simulationType = hkpWorldCinfo::SIMULATION_TYPE_CONTINUOUS;
			//------------
			//World Limits
			HavokWorldInfo.m_broadPhaseBorderBehaviour = hkpWorldCinfo::BROADPHASE_BORDER_FIX_ENTITY;
			HavokWorldInfo.setBroadPhaseWorldSize(1000.0f);
			//------------
			//------------WORLD CREATION------
				m_HWorld = new hkpWorld(HavokWorldInfo);
				m_HWorld->m_wantDeactivation = false;
				//World Block
				//para poder modificarlo.
				m_HWorld->markForWrite();
				//-------------
			//--------------------------------
			//Collition detect
			hkpAgentRegisterUtil::registerAllAgents(m_HWorld->getCollisionDispatcher());

		//-----------WORLD CONFIG END---------


		//-----------VISUAL DEBUGER CONFIG----
			//Visual Debugger Tnitialization
			m_HContext = new hkpPhysicsContext();
			hkpPhysicsContext::registerAllPhysicsProcesses();
			m_HContext->addWorld(m_HWorld);
			m_HWorld->unmarkForWrite();

			hkArray<hkProcessContext*> havokContexts;
			havokContexts.pushBack(m_HContext);

			m_VDebugger = new hkVisualDebugger(havokContexts);
			m_VDebugger->serve();
		//----------VISUAL DEBUGER CONFIG END--

		//----------TEST SCENE START---------
		//StartTestScene();
		//----------TEST SCENE START END---------

		//----------Initialized------------------
		HavokStarted = true;
		Instance = this;
		//----------Initialized------------------
	}
}

Physics* Physics::getInstance(){
	if(Instance == NULL){
		Instance = new Physics();
	}
	return Instance;
}

void Physics::StartTestScene(){
		//--------------------Test Scene--------------------
			//--------Floor---------
	hkpBoxShape* Floor = new hkpBoxShape(hkVector4(1000.0f, 10.0f, 1000.0f));

			hkpRigidBodyCinfo HavokRBodyInfo1;
			HavokRBodyInfo1.m_shape = Floor;
			HavokRBodyInfo1.m_position = hkVector4(0.0f, -10.0f, 0.0f);
			HavokRBodyInfo1.m_motionType = hkpMotion::MOTION_FIXED;
			Floor->setRadius(0.0f);
			m_RBody1 = new hkpRigidBody(HavokRBodyInfo1);

			m_HWorld->addEntity(m_RBody1);
			Floor->removeReference();
			//-------Floor end--------
		 //--------------------Test Scene--------------------
}

Physics::~Physics (){
/*	m_RBody1->removeReference();
	m_RBody1 = NULL;

	m_RBody2->removeReference();
	m_RBody2 = NULL;*/

	m_VDebugger->shutdown();
	m_VDebugger->removeReference();
	m_HContext->removeReference();

	m_HWorld->removeReference();

	hkBaseSystem::quit();
	hkMemoryInitUtil::quit();
}

void Physics::addEntity(pGr::RigidBody* rigidBody){
	m_HWorld->markForWrite();
	m_HWorld->addEntity(rigidBody->rigidbody());
	m_HWorld->unmarkForWrite();
}

void Physics::update (float DeltaTime){
	m_VDebugger->step();
	float fHavokStep = (DeltaTime / 1000.0f);
	if(fHavokStep < 0.00000001f) {
		return;
	}

	if(fHavokStep > 4.0f) {
		fHavokStep = 3.9f;
	}

	m_HWorld->stepDeltaTime(fHavokStep);
}

void Physics::HavokFailure (const char* msg, void* userAgent){
	OutputDebugString(msg);
}

#include <Common\Base\KeyCode.cxx>

#undef HK_FEATURE_PRODUCT_AI
#undef HK_FEATURE_PRODUCT_ANIMATION
#undef HK_FEATURE_PRODUCT_CLOTH
#undef HK_FEATURE_PRODUCT_DESTRUCTION
#undef HK_FEATURE_PRODUCT_DESTRUCTION_2012
#undef HK_FEATURE_PRODUCT_BEHAVIOUR
#undef HK_FEATURE_PRODUCT_MILSIM
#undef HK_FEATURE_PRODUCT_PHYSICS

#define HK_EXCLUDE_LIBRARY_hkpVehicle
#define HK_EXCLUDE_LIBRARY_hkCompat
#define HK_EXCLUDE_LIBRARY_hkSceneData
#define HK_EXCLUDE_LIBRARY_hkcdCollide

#define HK_EXCLUDE_FEATURE_SerializeDeprecatedPre700
#define HK_EXCLUDE_FEATURE_RegisterVersionPatches
#define HK_EXCLUDE_FEATURE_hkpHeightField
#define HK_EXCLUDE_FEATURE_hkpAccurateInertiaTensorComputer
#define HK_EXCLUDE_FEATURE_hkpUtilities
#define HK_EXCLUDE_FEATURE_hkpVehicle
#define HK_EXCLUDE_FEATURE_hkpCompressedMeshShape
#define HK_EXCLUDE_FEATURE_hkpConvexPieceMeshShape
#define HK_EXCLUDE_FEATURE_hkpExtendedMeshShape
#define HK_EXCLUDE_FEATURE_hkpMeshShape
#define HK_EXCLUDE_FEATURE_hkpSimpleMeshShape
#define HK_EXCLUDE_FEATURE_hkpPoweredChainData
#define HK_EXCLUDE_FEATURE_hkMonitorStream
#include <Common/Base/Config/hkProductFeatures.cxx>