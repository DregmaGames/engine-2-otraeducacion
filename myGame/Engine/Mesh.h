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

			void draw();
			//void Update(Timer& rkTimer);
			void setTexture(Texture& theTexture);
			void setTexture(std::string, DWORD theColor);
			void setData(const MeshVertex*, size_t vertexCount, pGr::Primitive, const unsigned short* pausIndices,size_t indexCount);

		protected:

			Texture s_Texture;
			Renderer& m_pkRenderer;
			Primitive m_pkPrimitive;
			IndexBuffer*	m_pkIndexBuffer;
			VertexBuffer*	m_pkVertexBuffer;
	};
}