#pragma once


#include <list>

#include "Game.h"
#include "Mesh.h"
#include "Node.h"
#include "Camera.h"
#include "Importer.h"
#include "pg1_input.h"
#include "pg1_timer.h"
#include "RenderTypes.h"
#include "pg1_directinput.h"


namespace Juego
{
	class MyGame : public pGr::Game
	{

	public:
		MyGame();
		bool init(pGr::Renderer&);
		void frame(pGr::Renderer&, pGr::DirectInput&, pGr::Timer& rkTimer);
		void inputs(pGr::Renderer& rkRenderer, pGr::DirectInput& rkInput, pGr::Timer& timer);
		void deinit();

	private:
		pGr::Node* pokemonNode;
		pGr::Node* rootNode;
		pGr::Mesh* mesh;
		pGr::Node* nodeMesh;

		pGr::Entity3D* lookForMesh(const std::string& name, const pGr::Node* rootNode);
	};
}