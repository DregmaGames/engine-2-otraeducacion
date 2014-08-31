#pragma once
#include "Entity2D.h"
#include "RenderTypes.h"
#include "pg2_vertexbuffer.h"
#include "pg2_indexbuffer.h"

namespace pGr{
	class Renderer;
	class Timer;
	class MYENGINE_API Mesh : public Entity2D{
		public:
			Mesh(Renderer&);
			~Mesh();
			void setData(const ColorVertex*, size_t vertexCount, pGr::Primitive, const unsigned short*, size_t indexCount);
			void Update(Timer& rkTimer){}
			void draw(Renderer& rkRenderer);
		protected:
			IndexBuffer*	m_pkIndexBuffer;
			VertexBuffer*	m_pkVertexBuffer;
			Primitive		m_pkPrimitive;
			Renderer&		m_pkRenderer;
	};
}