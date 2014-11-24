#include "Scene2.h"

#include "Node.h"
#include"RigidBody.h"
#include"Mesh.h"
#include"Collider.h"

bool Juego::Scene2::init(pGr::Renderer& renderer,pGr::Importer& importer){
	rootNode = new pGr::Node();
	//importer.import3DScene("assets/dragons.obj", *rootNode);
	importer.import3DScene("assets/Chari.obj", *rootNode);
	//rootNode->setPos(0,0,0);

	pGr::Node* nodeMesh = dynamic_cast<pGr::Node*>(lookForMesh("Cube.001_Cube.002", rootNode));
	mesh = dynamic_cast<pGr::Mesh*>(nodeMesh->childs()[0]);

	doRigidBodys(*rootNode);

	return true;
}

void Juego::Scene2::frame(pGr::Renderer& renderer ,pGr::Importer& importer, pGr::Game& game, pGr::DirectInput& dInput){
	//input camera.
	float movementSpeed = 0.1f;
	float rotationSpeed = 0.1f;

	//Aceletar//
	if(dInput.keyDown(pGr::Input::KEY_LSHIFT)){
		movementSpeed = 0.5f;
	}
	//Aceletar//

	//******Atras y adelante************//
	if(dInput.keyDown(pGr::Input::KEY_W)){
		renderer.m_pkCamera->walk(movementSpeed);
	}
	if(dInput.keyDown(pGr::Input::KEY_S)){
		renderer.m_pkCamera->walk(-movementSpeed);
	}
	//******Atras y adelante************//

	//******Girar derecha/izquierda************//
	if(dInput.keyDown(pGr::Input::KEY_D)){
		renderer.m_pkCamera->roll(rotationSpeed);
	}if(dInput.keyDown(pGr::Input::KEY_A)){
		renderer.m_pkCamera->roll(-rotationSpeed);
	}
	//******Girar derecha/izquierda************//

	//******Arriba y abajo************//
	if(dInput.keyDown(pGr::Input::KEY_SPACE)){
		renderer.m_pkCamera->fly(movementSpeed);
	}
	if(dInput.keyDown(pGr::Input::KEY_LCONTROL)){
		renderer.m_pkCamera->fly(-movementSpeed);
	}
	//******Arriba y abajo************//

	//******Moverse para los costados************//
	if(dInput.keyDown(pGr::Input::KEY_E)){
		renderer.m_pkCamera->strafe(movementSpeed);
	}
	if(dInput.keyDown(pGr::Input::KEY_Q)){
		renderer.m_pkCamera->strafe(-movementSpeed);
	}
	//******Moverse para los costados************//

	rootNode->updateTransformation();

	rootNode->draw();
}

bool Juego::Scene2::deInit(){
	return true;
}

void Juego::Scene2::doRigidBodys(pGr::Node& pkNode){				
	pGr::Physics* pkPhysics = pGr::Physics::getInstance();

	for(std::vector<pGr::Entity3D*>::const_iterator it = pkNode.childs().begin(); it != pkNode.childs().end(); it ++){
		pGr::Node* pNode = dynamic_cast<pGr::Node*>(*it);

		if(pNode){
			doRigidBodys(*pNode);
		}else{
			pGr::Mesh* cMesh = dynamic_cast<pGr::Mesh*>(*it);
			if(cMesh){
				pGr::MeshCollider* collider = new pGr::MeshCollider();
				collider->calculate(cMesh);
				cMesh->rigidBody()->setCollider(collider);
				cMesh->rigidBody()->setHavokMotion(pGr::RigidBody::HavokMotion::Static);
				pkPhysics->addEntity(cMesh->rigidBody());
			}
		}
	}
}

	pGr::Entity3D* lookForMesh(const std::string& name, const pGr::Node* rootNode)
	{
		for(std::vector<pGr::Entity3D*>::const_iterator it = rootNode->childs().begin(); it != rootNode->childs().end();it++)
		{
			if((*it)->getName() == name )
			{
				return (*it);
			}

			pGr::Node* childNode = dynamic_cast<pGr::Node*>(*it);
			if(childNode)
			{
				for(std::vector<pGr::Entity3D*>::const_iterator it = childNode->childs().begin(); it != childNode->childs().end();
					it++)
				{
					pGr::Entity3D* grandsonNode = lookForMesh(name, childNode);
					if(grandsonNode)
					{
						return grandsonNode;
					}
				}
			}
		}

		return NULL;
	}
