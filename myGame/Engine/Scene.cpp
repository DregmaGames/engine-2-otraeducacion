#include "Scene.h"
#include "Sprite.h"
#include "Quad.h"
#include "Renderer.h"
#include "pg1_timer.h"
using namespace pGr;
Scene::Scene(){
	
}
Scene::~Scene(){
	deInit();
}
/*void Scene::SearchObjByName(std::string& m_String,pGr::Entity2D* m_Entity){
	for (std::list<pGr::Entity2D*>::iterator it = m_kObjects.begin(); it != m_kObjects.begin(); it++){
		if(it->getName() == m_String){
			m_Entity = 
		}
	}
}
*/

void Scene::deInit(){
	for(int i=0; i < m_kObjects.size(); i++){
		delete m_kObjects[i];
		m_kObjects[i] = NULL;
	}
}

void Scene::drawScene(pGr::Renderer* mkRenderer, pGr::Timer* timer){

	for(int i = 0; i < m_kObjects.size(); i++)
	{
		if(m_kObjects[i]!=NULL){
			m_kObjects[i]->Update(*timer);
			m_kObjects[i]->draw(*mkRenderer);
		}
	}

}

bool Scene::getEntity(Sprite** Entity, std::string Name){
	if(m_kObjects.empty())
		return true;

	for(int i=0; i < m_kObjects.size(); i++){
		if(m_kObjects[i]->getName() == Name){
			*Entity = (Sprite*)m_kObjects[i];
			return true;
		}
	}
	return false;
}

bool Scene::getEntity(Quad** Entity, std::string Name){
	if(m_kObjects.empty())
		return true;

	for(int i=0; i < m_kObjects.size(); i++){
		if(m_kObjects[i]->getName() == Name){
			*Entity = (Quad*)m_kObjects[i];
			return true;
		}
	}
	return false;
}