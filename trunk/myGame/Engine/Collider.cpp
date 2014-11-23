#include "Collider.h"
#include "Mesh.h"
#include "pg2_indexbuffer.h"
#include "pg2_vertexbuffer.h"

#include <Common/Base/hkBase.h>
#include <Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Common/Base/Types/Geometry/hkStridedVertices.h>
#include <Physics2012/Collide/Shape/Convex/Box/hkpBoxShape.h>
#include <Physics2012/Collide/Shape/Convex/ConvexVertices/hkpConvexVerticesShape.h>

using namespace pGr;

Collider::Collider() : m_pkRigidBody(NULL){
}
Collider::~Collider(){
	m_pkRigidBody->removeReference();
	m_pkRigidBody = NULL;
}
void Collider::setPosition(float x,float y,float z){
	m_pkRigidBody->setPosition( hkVector4(x,y,z) );
}

BoxCollider::BoxCollider()	:	Collider(),	m_pkBox(NULL){

}

BoxCollider::~BoxCollider(){

}

void BoxCollider::calculate(const Mesh* pkMesh){

}

hkpShape* BoxCollider::shape(){
	return m_pkBox;
}

MeshCollider::MeshCollider() :	Collider(),	m_pkMeshCollider(NULL){

}

MeshCollider::~MeshCollider(){
}

void MeshCollider::calculate(const Mesh* pkMesh){
	size_t iCount = pkMesh->indexs().size();
	hkArray<hkVector4> aVertexs(iCount);
	for(unsigned int i=0; i < iCount; i++){
		aVertexs[i].set( -pkMesh->vertexs()[pkMesh->indexs()[i]].x,
						  pkMesh->vertexs()[pkMesh->indexs()[i]].y, 
						  pkMesh->vertexs()[pkMesh->indexs()[i]].z);
	}

	hkStridedVertices StridedVertices(aVertexs);
	m_pkMeshCollider = new hkpConvexVerticesShape(StridedVertices);

	hkpRigidBodyCinfo	rbInfo;
	rbInfo.m_shape = m_pkMeshCollider;
	rbInfo.m_position = hkVector4(0.0f,0.0f,0.0f);
	rbInfo.m_motionType = hkpMotion::MOTION_FIXED;

	m_pkRigidBody = new hkpRigidBody(rbInfo);
	m_pkMeshCollider->removeReference();
}
hkpShape* MeshCollider::shape(){
	return m_pkMeshCollider;
}