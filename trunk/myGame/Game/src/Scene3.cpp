#include "Scene3.h"
#include "Renderer.h"
#include "Camera.h"
using namespace Juego;

void Scene3::frame(pGr::Renderer& r ,pGr::Importer& importer, pGr::Game& game, pGr::DirectInput& dInput){
	m_Pkmesh->draw(r);
}


bool Scene3::init(pGr::Renderer& r){
	m_Pkmesh =new pGr::Mesh(r);
	pGr::ColorVertex* MkVertex=new pGr::ColorVertex;
	MkVertex[0].x = -0.5; MkVertex[0].y = 0.5; MkVertex[0].z = 0.5;
	MkVertex[1].x = 0.5; MkVertex[1].y = 0.5; MkVertex[1].z = 0.5;
	MkVertex[2].x = -0.5; MkVertex[2].y = -0.5; MkVertex[2].z = 0.5;
	MkVertex[3].x = 0.5; MkVertex[3].y = -0.5; MkVertex[3].z = 0.5;

	MkVertex[0].color = PG1_COLOR_ARGB(128,0,0,0);
	MkVertex[1].color = PG1_COLOR_ARGB(128,0,0,0);
	MkVertex[2].color = PG1_COLOR_ARGB(128,0,0,0);
	MkVertex[3].color = PG1_COLOR_ARGB(128,0,0,0);

	m_Pkmesh->setData(MkVertex,4,pGr::TriangleList,new USHORT(2),2);
	return true;
}
