#include "Mesh.h"
#include "Renderer.h"
#include "RenderTypes.h"
using namespace pGr;

/*Mesh::Mesh(Renderer& p_Renderer) : m_pkRenderer(p_Renderer)
{
	m_pkVertexBuffer = m_pkRenderer.CreateVB(sizeof(pGr::MeshVertex), pGr::MeshVertexType);
	m_pkIndexBuffer	 = m_pkRenderer.CreateIB();
}

Mesh::~Mesh()
{
	if(m_pkIndexBuffer){
		delete m_pkIndexBuffer;
		m_pkIndexBuffer = NULL;
	}
	if(m_pkVertexBuffer){
		delete	m_pkVertexBuffer;
		m_pkVertexBuffer = NULL;
	}
}

void Mesh::setData(const MeshVertex* the_vertex, size_t vertexCount, Primitive thePrimitive, const unsigned short* pausIndices, size_t indexCount)
{
	m_pkPrimitive = thePrimitive;
	m_pkVertexBuffer->setVertexData((void*) the_vertex, vertexCount);
	m_pkIndexBuffer->setIndexData(pausIndices,indexCount);
}

void Mesh::draw()
{
	m_pkVertexBuffer->bind();
	m_pkIndexBuffer->bind();
	m_pkRenderer.setCurrentTexture(s_Texture);
	m_pkRenderer.setMatrix(World, m_pkTransformationMatrix);
	m_pkRenderer.draw(&m_pkPrimitive);
}

void Mesh::setTexture(std::string pkTextureFile, DWORD theColor)
{
	s_Texture = m_pkRenderer.loadTexture(pkTextureFile,theColor);
}

void Mesh::setTexture(Texture& theTexture)
{
	s_Texture = theTexture;
}*/

Mesh::Mesh(Renderer & p_Renderer): m_pkRenderer(p_Renderer) , s_Texture(NoTexture){
	m_pkVertexBuffer = m_pkRenderer.CreateVB(sizeof(pGr::MeshVertex), pGr::MeshVertexType);
	m_pkIndexBuffer = m_pkRenderer.CreateIB();
}

Mesh::~Mesh(){
	
	m_pkVertex.clear();
	m_pkIndex.clear();

	if(m_pkVertexBuffer){
		delete m_pkVertexBuffer;
		m_pkVertexBuffer = NULL;
	}
	if(m_pkIndexBuffer){
		delete m_pkIndexBuffer;
		m_pkIndexBuffer = NULL;
	}

}

void Mesh::setData(const MeshVertex* Tex_Vertex, size_t vertexCount, pGr::Primitive Prim, const unsigned short* pInt, size_t indexCount){
	m_pkPrimitive = Prim;
	m_pkVertexBuffer->setVertexData((void *)Tex_Vertex, vertexCount);
	m_pkIndexBuffer->setIndexData(pInt,indexCount);


	// Guardo Vertex
	m_pkVertex.resize(vertexCount);
	memcpy( &( m_pkVertex.front() ), Tex_Vertex, vertexCount * sizeof(MeshVertex) );


	// Guardo Index
	m_pkIndex.resize(indexCount);
	memcpy( &( m_pkIndex.front() ), pInt, indexCount * sizeof(unsigned short) );


}

void Mesh::draw(){
	m_pkVertexBuffer->bind();
	m_pkIndexBuffer->bind();
	m_pkRenderer.setCurrentTexture(s_Texture);
	m_pkRenderer.setMatrix(World, m_pkTransformationMatrix);
	m_pkRenderer.draw(&m_pkPrimitive);
}

void Mesh::setTexture(std::string pkTextureFile, DWORD theColor){
	s_Texture = m_pkRenderer.loadTexture(pkTextureFile,theColor);
}

void Mesh::setTexture(Texture& theTexture){
	s_Texture = theTexture;
}

const std::vector<MeshVertex>& Mesh::vertexs() const{
	return m_pkVertex;
}

const std::vector<unsigned short> Mesh::indexs() const{
	return m_pkIndex;
}