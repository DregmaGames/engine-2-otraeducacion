#pragma once
#include "Scene.h"
#include "Sprite.h"
#include "Quad.h"
#include "Renderer.h"
#include "pg1_timer.h"
#include "pg1_directinput.h"
#include "testGame.h"
#include "Mesh.h"
#include "RenderTypes.h"

namespace Juego{
	class Scene2 : public pGr::Scene{
	public:
		void frame(pGr::Renderer&,pGr::Importer&, pGr::Game&, pGr::DirectInput&);
		bool init(pGr::Renderer&,pGr::Importer&);
		bool deInit();
	public:
		pGr::Mesh* theMesh;
	};
}