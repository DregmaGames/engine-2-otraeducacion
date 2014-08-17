#pragma once
#include "Game.h"
#include "Quad.h"
#include "Sprite.h"
#include "RenderTypes.h"
#include "pg1_directinput.h"
#include "pg1_input.h"
#include "pg1_timer.h"
#include <list>
#include "Scene1.h"
#include "Scene2.h"
namespace Juego{
	class Scene1;
	class Scene2;
	class MyGame : public pGr::Game{
	public:
		MyGame();
		bool init(pGr::Renderer&,pGr::Importer&);
		void frame(pGr::Renderer&,pGr::DirectInput&,pGr::Timer& rkTimer,pGr::Importer&);
		void deinit();
		Scene1* m_kScene;
		Scene2* m_Scene2;
	};
}