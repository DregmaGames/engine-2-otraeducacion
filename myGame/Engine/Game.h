#ifndef GAME_H
#define GAME_H

#include "myEngine_API.h"
#include <vector>
#include <string>
#include "Node.h"
//---------------------------------------
namespace pGr
{
	class Renderer;
	class DirectInput;
	class Timer;
	class Importer;
	class Scene;
	class MYENGINE_API Game
	{
	public:
		virtual bool init (pGr::Renderer&,pGr::Importer&)=0;
		virtual void frame(pGr::Renderer&,pGr::DirectInput& rkInput, pGr::Timer& t,pGr::Importer&)=0;
		virtual void deinit()=0;

		pGr::Scene* getCurrentScene() { return currentScene;};
		void setCurrentScene(std::string, pGr::Importer&, std::string, pGr::Renderer&);
		void addScene(Scene*);
	protected:
		std::vector<pGr::Scene*> scene_List;
		Scene* currentScene;
		Node* N_CurrentScene;
	};
}
#endif