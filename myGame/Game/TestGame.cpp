#include "TestGame.h"
#include "Renderer.h"
#include"RigidBody.h"
#include"Collider.h"
//---------------------------------------
using namespace Juego;
//---------------------------------------
 MyGame::MyGame()
 {
 }
 bool MyGame::init(pGr::Renderer& rkRenderer,pGr::Physics& rkPhysics)
{
	rootNode = new pGr::Node();
	//importer.import3DScene("assets/dragons.obj", *rootNode);
	pGr::Importer* importer = pGr::Importer::getInstance();
	importer->init(&rkRenderer);
	importer->import3DScene("assets/PokemonNew/BR_Kyogre.obj", *rootNode);
	//rootNode->setPos(0,0,0);
	
	//pGr::Node* nodeMesh = dynamic_cast<pGr::Node*>(lookForMesh("Cube.001_Cube.002", rootNode));
	//pGr::Node* nodeMesh = dynamic_cast<pGr::Node*>(lookForMesh("polygon2.002", rootNode));
	//pGr::Node* nodeMesh = dynamic_cast<pGr::Node*>(lookForMesh("Box001", rootNode));
	pGr::Node* nodeMesh = dynamic_cast<pGr::Node*>(lookForMesh("polygon0.001", rootNode));
	mesh = dynamic_cast<pGr::Mesh*>(nodeMesh->childs()[0]);

	doRigidBodys(*rootNode);

	return true;
}
//---------------------------------------
void MyGame::frame (pGr::Renderer& rkRenderer, pGr::DirectInput& rkInput,pGr::Timer& rkTimer)
{
	//input camera.
	float movementSpeed = 0.1f;
	float rotationSpeed = 0.1f;

	//Aceletar//
	if(rkInput.keyDown(pGr::Input::KEY_LSHIFT)){
		movementSpeed = 0.5f;
	}
	//Aceletar//

	//******Atras y adelante************//
	if(rkInput.keyDown(pGr::Input::KEY_W)){
		rkRenderer.m_pkCamera->walk(movementSpeed);
	}
	if(rkInput.keyDown(pGr::Input::KEY_S)){
		rkRenderer.m_pkCamera->walk(-movementSpeed);
	}
	//******Atras y adelante************//

	//******Girar derecha/izquierda************//
	if(rkInput.keyDown(pGr::Input::KEY_D)){
		rkRenderer.m_pkCamera->roll(rotationSpeed);
	}if(rkInput.keyDown(pGr::Input::KEY_A)){
		rkRenderer.m_pkCamera->roll(-rotationSpeed);
	}
	//******Girar derecha/izquierda************//

	//******Arriba y abajo************//
	if(rkInput.keyDown(pGr::Input::KEY_SPACE)){
		rkRenderer.m_pkCamera->fly(movementSpeed);
	}
	if(rkInput.keyDown(pGr::Input::KEY_LCONTROL)){
		rkRenderer.m_pkCamera->fly(-movementSpeed);
	}
	//******Arriba y abajo************//

	//******Moverse para los costados************//
	if(rkInput.keyDown(pGr::Input::KEY_E)){
		rkRenderer.m_pkCamera->strafe(movementSpeed);
	}
	if(rkInput.keyDown(pGr::Input::KEY_Q)){
		rkRenderer.m_pkCamera->strafe(-movementSpeed);
	}
	//******Moverse para los costados************//

	rootNode->updateTransformation();

	rootNode->draw();
}
//---------------------------------------
void MyGame::deinit()
{
	
}
//---------------------------------------
void MyGame::doRigidBodys(pGr::Node& pkNode){				
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
				cMesh->getRigidBody()->setCollider(collider);
				cMesh->getRigidBody()->setHavokMotion(pGr::RigidBody::HavokMotion::Static);
				pkPhysics->addEntity(cMesh->getRigidBody());
			}
		}
	}
}

	pGr::Entity3D* MyGame::lookForMesh(const std::string& name, const pGr::Node* rootNode)
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