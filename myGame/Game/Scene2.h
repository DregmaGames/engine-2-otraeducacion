#pragma once
#include "Scene.h"
#include "Sprite.h"
#include "Quad.h"
#include "Renderer.h"
#include "Importer.h"
#include "pg1_timer.h"
#include "pg1_directinput.h"
#include "testGame.h"
#include "RenderTypes.h"

namespace Juego{

	class Node;
	
	class Scene2 : public pGr::Scene{

		public:

			void frame(pGr::Renderer&,pGr::Importer&, pGr::Game&, pGr::DirectInput&);
			bool init(pGr::Renderer&,pGr::Importer&);
			bool deInit();

			pGr::Mesh* theMesh;
	};
}