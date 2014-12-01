#include "TestGame.h"
#include "Renderer.h"
#include "RigidBody.h"
#include "Collider.h"
#include <iostream>
//---------------------------------------
using namespace Juego;
float timer = 0; //no tocar.
//---------------------------------------
MyGame::MyGame()
{
}
bool MyGame::init(pGr::Renderer& rkRenderer, pGr::Physics& rkPhysics)
{
	rootNode = new pGr::Node();
	pokemonNode = new pGr::Node();

	pGr::Importer* importer = pGr::Importer::getInstance();
	importer->init(&rkRenderer);
	importer->import3DScene("assets/PokemonNew/BR_Kyogre.obj", *rootNode);

	rootNode->setPosition(0, 0, 0);
	/*nodeMesh = dynamic_cast<pGr::Node*>(lookForMesh("polygon0.001", rootNode));
	mesh = dynamic_cast<pGr::Mesh*>(nodeMesh->childs()[0]);
	rootNode->addChild(pokemonNode);
	pokemonNode->setParent(rootNode);
	pokemonNode->addChild(nodeMesh);
	nodeMesh->setParent(pokemonNode);
	*/
	doRigidBodys(*rootNode);
	return true;
}
//---------------------------------------
void MyGame::frame(pGr::Renderer& rkRenderer, pGr::DirectInput& rkInput, pGr::Timer& rkTimer)
{
	timer += rkTimer.timeBetweenFrames();
	if (rootNode)
	{
		rootNode->updateTransformation();
		rootNode->LookingBox(*rootNode);
		//rootNode->draw();
	}
	//hardcodeo para que no se caguen las inputs(por tener tantos fps, haha
	//si tenes menos de 60 fps, se caga igual...
	if (timer < 30) return;
	timer = 0;
	//------------------------------------------
	inputs(rkRenderer, rkInput);
	//------------------------------------------
}

void MyGame::inputs(pGr::Renderer& rkRenderer, pGr::DirectInput& rkInput)
{
	float movementSpeed = 1.0f;
	float rotationSpeed = 0.3f;
	/***********************************************************************************************************/
	if (rkInput.keyDown(pGr::Input::KEY_F1)){
		rootNode->setRotationY(rootNode->getRotationY() + rotationSpeed);
	}

	if (rkInput.keyDown(pGr::Input::KEY_F2)){
		rootNode->setRotationY(rootNode->getRotationY() - rotationSpeed);
	}

	if (rkInput.keyDown(pGr::Input::KEY_UP))
	{
		rootNode->setPositionZ(rootNode->getPosZ() - movementSpeed);
	}
	//
	if (rkInput.keyDown(pGr::Input::KEY_DOWN))
	{
		rootNode->setPositionZ(rootNode->getPosZ() + movementSpeed);
	}
	//
	if (rkInput.keyDown(pGr::Input::KEY_RIGHT))
	{
		rootNode->setPositionX(rootNode->getPosX() - movementSpeed);
	}

	if (rkInput.keyDown(pGr::Input::KEY_LEFT))
	{
		rootNode->setPositionX(rootNode->getPosX() + movementSpeed);
	}
	/*******************************************************************************************************/
	//Aceletar//
	if (rkInput.keyDown(pGr::Input::KEY_LSHIFT)){
		movementSpeed = movementSpeed * 2;
		rotationSpeed = rotationSpeed * 2;

	}
	//Aceletar//

	//******Atras y adelante************//
	if (rkInput.keyDown(pGr::Input::KEY_W)){
		rkRenderer.m_pkCamera->walk(movementSpeed);
	}
	if (rkInput.keyDown(pGr::Input::KEY_S)){
		rkRenderer.m_pkCamera->walk(-movementSpeed);
	}
	//******Atras y adelante************//

	//******Girar derecha/izquierda************//
	if (rkInput.keyDown(pGr::Input::KEY_D)){
		rkRenderer.m_pkCamera->roll(rotationSpeed);
	}if (rkInput.keyDown(pGr::Input::KEY_A)){
		rkRenderer.m_pkCamera->roll(-rotationSpeed);
	}
	//******Girar derecha/izquierda************//

	//******Arriba y abajo************//
	if (rkInput.keyDown(pGr::Input::KEY_SPACE)){
		rkRenderer.m_pkCamera->fly(movementSpeed);
	}
	if (rkInput.keyDown(pGr::Input::KEY_LCONTROL)){
		rkRenderer.m_pkCamera->fly(-movementSpeed);
	}
	//******Arriba y abajo************//

	//******Moverse para los costados************//
	if (rkInput.keyDown(pGr::Input::KEY_E)){
		rkRenderer.m_pkCamera->strafe(movementSpeed);
	}
	if (rkInput.keyDown(pGr::Input::KEY_Q)){
		rkRenderer.m_pkCamera->strafe(-movementSpeed);
	}
	//******Moverse para los costados************//

	if (rkInput.keyDown(pGr::Input::KEY_O)){
		rkRenderer.wireframe(true);
	}
	if (rkInput.keyDown(pGr::Input::KEY_P)){
		rkRenderer.wireframe(false);
	}
}
//---------------------------------------
void MyGame::deinit()
{

}
//---------------------------------------
void MyGame::doRigidBodys(pGr::Node& pkNode){
	pGr::Physics* pkPhysics = pGr::Physics::getInstance();

	for (std::vector<pGr::Entity3D*>::const_iterator it = pkNode.childs().begin(); it != pkNode.childs().end(); it++){
		pGr::Node* pNode = dynamic_cast<pGr::Node*>(*it);

		if (pNode){
			doRigidBodys(*pNode);
		}
		else{
			pGr::Mesh* cMesh = dynamic_cast<pGr::Mesh*>(*it);
			if (cMesh){
				pGr::MeshCollider* collider = new pGr::MeshCollider();
				collider->calculate(cMesh);
				cMesh->getRigidBody()->setCollider(collider);
				cMesh->getRigidBody()->setHavokMotion(pGr::RigidBody::HavokMotion::Dynamic);
				pkPhysics->addEntity(cMesh->getRigidBody());
			}
		}
	}
}
pGr::Entity3D* MyGame::lookForMesh(const std::string& name, const pGr::Node* rootNode)
{
	for (std::vector<pGr::Entity3D*>::const_iterator it = rootNode->childs().begin(); it != rootNode->childs().end(); it++)
	{
		if ((*it)->getName() == name)
		{
			return (*it);
		}

		pGr::Node* childNode = dynamic_cast<pGr::Node*>(*it);
		if (childNode)
		{
			for (std::vector<pGr::Entity3D*>::const_iterator it = childNode->childs().begin(); it != childNode->childs().end();
				it++)
			{
				pGr::Entity3D* grandsonNode = lookForMesh(name, childNode);
				if (grandsonNode)
				{
					return grandsonNode;
				}
			}
		}
	}
	return NULL;
}
