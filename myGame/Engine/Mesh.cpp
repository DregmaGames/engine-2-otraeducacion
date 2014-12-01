#include "Mesh.h"
#include "Renderer.h"
#include "RenderTypes.h"
using namespace pGr;

int Mesh::amountDraw = 0; //Just for debbug.
Mesh::Mesh(Renderer & p_Renderer) : m_rkRenderer(p_Renderer), m_kTexture(NoTexture){
	m_pkVertexBuffer = m_rkRenderer.CreateVB(sizeof(pGr::MeshVertex), pGr::MeshVertexType);
	m_pkIndexBuffer = m_rkRenderer.CreateIB();
}

Mesh::~Mesh(){
	m_kVertex.clear();
	m_kIndex.clear();

	if (m_pkVertexBuffer){
		delete m_pkVertexBuffer;
		m_pkVertexBuffer = NULL;
	}
	if (m_pkIndexBuffer){
		delete m_pkIndexBuffer;
		m_pkIndexBuffer = NULL;
	}
}

void Mesh::setMeshData(const MeshVertex* Tex_Vertex, size_t vertexCount, pGr::Primitive Prim, const unsigned short* pInt, size_t indexCount){
	m_kPrimitive = Prim;
	m_pkVertexBuffer->setVertexData((void *)Tex_Vertex, vertexCount);
	m_pkIndexBuffer->setIndexData(pInt, indexCount);

	// Save vertex
	m_kVertex.resize(vertexCount);
	memcpy(&(m_kVertex.front()), Tex_Vertex, vertexCount * sizeof(MeshVertex));

	// Save index
	m_kIndex.resize(indexCount);
	memcpy(&(m_kIndex.front()), pInt, indexCount * sizeof(unsigned short));
}

void Mesh::draw(){
	amountDraw++; //Just for debbug.
	m_pkVertexBuffer->bind();
	m_pkIndexBuffer->bind();
	m_rkRenderer.setCurrentTexture(m_kTexture);
	m_rkRenderer.setMatrix(World, m_pkTransformationMatrix);
	m_rkRenderer.draw(m_kPrimitive);
}

void Mesh::setTexture(std::string pkTextureFile, DWORD theColor){
	m_kTexture = m_rkRenderer.loadTexture(pkTextureFile, theColor);
}

void Mesh::setTexture(Texture& theTexture){
	m_kTexture = theTexture;
}

const std::vector<MeshVertex>& Mesh::vertexs() const{
	return m_kVertex;
}

const std::vector<unsigned short> Mesh::indexs() const{
	return m_kIndex;
}