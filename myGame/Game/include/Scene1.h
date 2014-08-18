#pragma once
#include "Scene.h"
#include "Sprite.h"
#include "Quad.h"
#include "Renderer.h"
#include "pg1_timer.h"
#include "pg1_directinput.h"
#include "testGame.h"

namespace Juego{
	class Scene1 : public pGr::Scene{
		public:
		void frame(pGr::Renderer&,pGr::Importer&, pGr::Game&, pGr::DirectInput&);
		bool init();

		private:
			pGr::Quad* _Quad;
			pGr::Sprite* _Sprite;
	};
}