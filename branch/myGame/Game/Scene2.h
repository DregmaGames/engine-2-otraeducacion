#pragma once

#include<sstream>
#include<string>
#include "Scene.h"
#include "Sprite.h"
#include "Quad.h"
#include "Renderer.h"
#include "Importer.h"
#include "pg1_timer.h"
#include "pg1_directinput.h"
#include "testGame.h"
#include "RenderTypes.h"
#include "Entity3D.h"

namespace Juego{

	class Node;
	class Entity3D;
	
	class Scene2 : public pGr::Scene{

		public:

			void frame(pGr::Renderer&,pGr::Importer&, pGr::Game&, pGr::DirectInput&);
			bool init(pGr::Renderer&,pGr::Importer&);
			bool deInit();
			void doRigidBodys(pGr::Node & pkNode);
			pGr::Entity3D* lookForMesh(const std::string& name, const pGr::Node* rootNode);

			pGr::Mesh* mesh;

	};
}