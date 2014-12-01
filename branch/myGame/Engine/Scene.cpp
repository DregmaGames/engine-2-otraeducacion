#include "Scene.h"
#include "Renderer.h"
#include "pg1_timer.h"
#include "Node.h"
#include "Mesh.h"

using namespace pGr;

Scene::Scene() : rootNode(NULL) 
{
	//Nothing to do.
}
Scene::~Scene() 
{
	deInit();
}

void Scene::deInit()
{
	for(int i=0; i < m_pkEntity3D.size(); i++){
		delete m_pkEntity3D[i];
		m_pkEntity3D[i] = NULL;
	}
}

void Scene::drawScene(pGr::Renderer* mkRenderer, pGr::Timer* timer)
{
	for(int i=0; i < m_pkEntity3D.size(); i++){
		m_pkEntity3D[i]->draw();
	}

	if(rootNode != NULL)
	{
		//rootNode->updateTransformation();
		rootNode->draw();
	}
}

bool Scene::addEntity(Entity3D* Entity){
	m_pkEntity3D.push_back(Entity);
	return true;
}

bool Scene::getNode(Node& theNodeDir){
	theNodeDir = *rootNode;
	return true;
}

bool Scene::getEntity(Mesh** Entity, std::string Name){
	if(m_pkEntity3D.empty()) return false;
	for(int i=0; i < m_pkEntity3D.size(); i++){
		if(m_pkEntity3D[i]->getName() == Name){
			*Entity = (Mesh*)m_pkEntity3D[i];
			return true;
		}
	}
	return false;
}