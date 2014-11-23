#ifndef SCENE_H
#define SCENE_H

#include "Entity3D.h"
#include "Animation.h"
#include "Importer.h"
#include "Engine.h"
#include "myEngine_API.h"
#include <string>
#include <vector>
using namespace std;
namespace pGr{

	class Game;
	class Node;
	class Timer;
	class Quad;
	class Sprite;
	class Importer;
	class Renderer;

	class MYENGINE_API Scene{

		public:

			Scene();
			~Scene();
			virtual bool init(pGr::Importer&) { return true; }
			virtual void frame(pGr::Renderer&,pGr::Importer&, pGr::Game&, pGr::DirectInput&){};
			void deInit();

			void drawScene(pGr::Renderer*, pGr::Timer*);
			bool getEntity(Mesh**, std::string);
			bool getNode(Node& theNodeDir);
			bool addEntity(Entity3D*);
			
			char* xmlPath;
			Node* node;
			std::string m_pkName;
			std::vector<Entity3D*> m_pkEntity3D;
	};
}
#endif