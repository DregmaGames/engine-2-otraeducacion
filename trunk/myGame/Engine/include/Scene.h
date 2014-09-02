#ifndef SCENE_H
#define SCENE_H

#include "Entity2D.h"
#include "Animation.h"
#include "Importer.h"
#include "MyEngine.h"
#include "myEngine_API.h"
#include <string>
#include <vector>
using namespace std;
namespace pGr{
	class Timer;
	class Renderer;
	class Quad;
	class Sprite;
	class Game;
	class MYENGINE_API Scene{
	public:
		Scene();
		~Scene();
		virtual void frame(pGr::Renderer&,pGr::Importer&, pGr::Game&, pGr::DirectInput&) { };
		virtual bool init(pGr::Renderer&,pGr::Importer&) { return true; }
		void drawScene(pGr::Renderer*, pGr::Timer*);
		bool getEntity(Sprite**, std::string);
		bool getEntity(Quad**, std::string);
		void deInit();
		char* xmlPath;
		std::string m_pkName;
	public:
		std::vector<pGr::Entity2D*> m_kObjects;
	};
}
#endif