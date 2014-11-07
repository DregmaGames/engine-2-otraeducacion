#ifndef SCENE_H
#define SCENE_H

#include "Entity2D.h"
#include "Entity3D.h"
#include "Animation.h"
#include "Importer.h"
#include "MyEngine.h"
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
			virtual void frame(pGr::Renderer&,pGr::Importer&, pGr::Game&, pGr::DirectInput&){};
			virtual bool init(pGr::Importer&) { return true; }
			void drawScene(pGr::Renderer*, pGr::Timer*);
			bool getEntity(Sprite**, std::string);
			bool getEntity(Quad**, std::string);
			bool getEntity(Mesh**, std::string);
			bool getNode(Node& theNodeDir);
			bool addEntity(Entity3D*);
			void deInit();
			char* xmlPath;
			Node* node;
			std::string m_pkName;
			std::vector<pGr::Entity2D*> m_kObjects;
			std::vector<Entity3D*> m_pkEntidades3D;
	};
}
#endif