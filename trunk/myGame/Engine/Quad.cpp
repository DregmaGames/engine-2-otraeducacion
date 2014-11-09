#include "quad.h"
#include "Renderer.h"
#include <d3dx9.h>
using namespace pGr;

Quad::Quad ()
	:
	Entity3D(),
	m_pakVertices ( new ColorVertex[4])
	{
		m_pakVertices[0].x = -0.5; m_pakVertices[0].y = 0.5; m_pakVertices[0].z = 0.5;
		m_pakVertices[1].x = 0.5; m_pakVertices[1].y = 0.5; m_pakVertices[1].z = 0.5;
		m_pakVertices[2].x = -0.5; m_pakVertices[2].y = -0.5; m_pakVertices[2].z = 0.5;
		m_pakVertices[3].x = 0.5; m_pakVertices[3].y = -0.5; m_pakVertices[3].z = 0.5;

		m_pakVertices[0].color = PG1_COLOR_ARGB(128,0,0,0);
		m_pakVertices[1].color = PG1_COLOR_ARGB(128,0,0,0);
		m_pakVertices[2].color = PG1_COLOR_ARGB(128,0,0,0);
		m_pakVertices[3].color = PG1_COLOR_ARGB(128,0,0,0);
		updateLocalTransformation();
	}
 Quad:: ~Quad ()
 {
	 delete m_pkTransformationMatrix;
	 m_pkTransformationMatrix= NULL;
	 delete[] m_pakVertices;
	 m_pakVertices =NULL;
 }
 void Quad::draw (Renderer& rRenderer)
 {
	 rRenderer.setCurrentTexture(NoTexture);
	 rRenderer.setMatrix(World, m_pkTransformationMatrix);
	 rRenderer.draw(m_pakVertices,pGr::TriangleStrip,4);
 }


 