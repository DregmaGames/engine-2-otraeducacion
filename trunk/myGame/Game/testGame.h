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
		bool init(pGr::Renderer&,pGr::Physics& physics);
		void frame(pGr::Renderer&,pGr::DirectInput&,pGr::Timer& rkTimer);
		void deinit();

		pGr::Node* rootNode;

		void doRigidBodys(pGr::Node & pkNode);
			
		
	private:

		pGr::Mesh* mesh;

		pGr::Entity3D* lookForMesh(const std::string& name, const pGr::Node* rootNode);
		
	};
}