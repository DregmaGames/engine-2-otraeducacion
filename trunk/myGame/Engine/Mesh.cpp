#include "Mesh.h"
#include "Renderer.h"
#include "RenderTypes.h"
using namespace pGr;

Mesh::Mesh(Renderer& p_Renderer) : m_pkRenderer(p_Renderer){
	m_pkVertexBuffer = m_pkRenderer.CreateVB(sizeof(pGr::ColorVertex), pGr::ColorVertexType);
	m_pkIndexBuffer	 = m_pkRenderer.CreateIB();
}

Mesh::~Mesh(){
	if(m_pkIndexBuffer){
		delete m_pkIndexBuffer;
		m_pkIndexBuffer = NULL;
	}
	if(m_pkVertexBuffer){
		delete	m_pkVertexBuffer;
		m_pkVertexBuffer = NULL;
	}
}

void Mesh::setData(const ColorVertex* the_vertex, size_t vertexCount, pGr::Primitive thePrimitive, const unsigned short* pausIndices, size_t indexCount){
	m_pkPrimitive = thePrimitive;
	m_pkVertexBuffer->setVertexData((void*) the_vertex, vertexCount);
	m_pkIndexBuffer->setIndexData(pausIndices,indexCount);
}

void Mesh::draw(Renderer& theRenderer){
	
	m_pkVertexBuffer->bind();
	m_pkIndexBuffer->bind();
	theRenderer.setCurrentTexture(NoTexture);
	theRenderer.setMatrix(World, m_pkTransformationMatrix);
	theRenderer.draw(&m_pkPrimitive);
}