/*#include "Game.h"
using namespace pGr;
pGr::Scene Game::getCurrentScene(){
	return 
}
void Game::setCurrentScene(){
	for(int i=0;i<scene_List.size();i++){
		scene_List[i]
	}
}*/

#include "Game.h"
#include "Scene.h"
using namespace pGr;

void Game::addScene(Scene* pkScene){
	scene_List.push_back(pkScene);
}
void Game::setCurrentScene(std::string pkString, pGr::Importer& importer, std::string fName, pGr::Renderer& m_pKrenderer){
	if(!currentScene) return;
	if(currentScene->m_pkName == pkString) return;
	if(scene_List.empty()) return;

	std::vector<Scene*>::iterator it;
	for(it = scene_List.begin(); it != scene_List.end(); it++){
		if( (*it._Ptr)->m_pkName == pkString){
			currentScene->deInit();
			currentScene = *it._Ptr; 
			// ASDFGH
			importer.importScene(fName,*currentScene);
			currentScene->init(m_pKrenderer,importer);
			return;
		}
	}
}