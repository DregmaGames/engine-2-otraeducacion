#pragma once
#include "Scene.h"
#include "Renderer.h"
#include "pg1_timer.h"
#include "pg1_directinput.h"
#include "testGame.h"
#include "Mesh.h"
namespace Juego{
	class Scene3 : public pGr::Scene{
		public:
		void frame(pGr::Renderer&,pGr::Importer&, pGr::Game&, pGr::DirectInput&);
		bool init(pGr::Renderer& r);
		private:
			pGr::Mesh* m_Pkmesh;
	};
}