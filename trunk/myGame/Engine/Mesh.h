#pragma once
#include "Entity3D.h"
#include "RenderTypes.h"
#include "pg2_vertexbuffer.h"
#include "pg2_indexbuffer.h"

namespace pGr
{
	class Renderer;
	class Timer;

	class MYENGINE_API Mesh : public Entity3D{
	public:

		Mesh(Renderer&);
		~Mesh();

		static int amountDraw; //Just for debbug

		void draw();

		void setTexture(Texture& theTexture);
		void setTexture(std::string, DWORD theColor);
		void setMeshData(const MeshVertex*, size_t vertexCount, pGr::Primitive, const unsigned short* pausIndices, size_t indexCount);

		const VertexBuffer* vertexBuffer() const;
		const IndexBuffer* indexBuffer() const;

		const std::vector<MeshVertex>& vertexs() const;
		const std::vector<unsigned short> indexs() const;

	protected:
		Texture m_kTexture;
		Primitive m_kPrimitive;

		Renderer& m_rkRenderer;

		IndexBuffer* m_pkIndexBuffer;
		VertexBuffer* m_pkVertexBuffer;

	private:
		std::vector<MeshVertex> m_kVertex;
		std::vector<unsigned short> m_kIndex;
	};
}