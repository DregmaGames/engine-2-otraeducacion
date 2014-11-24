#ifndef QUAD_H
#define QUAD_H
#include "myEngine_API.h"
#include "RenderTypes.h"
#include "Entity3D.h"
#include <list>

namespace pGr
{
	class Renderer;
	class Timer;
	class MYENGINE_API Quad:public Entity3D
	{
	public:
		Quad();
		~Quad();

	public:
		void draw (Renderer& rkRenderer);
		void Update(Timer& rkTimer){ }
		void Quad::setColor(DWORD c){
		 for(int i = 0; i < 4; i++)
 			m_pakVertices[i].color = c;
		}
		void Quad::setColor(DWORD c, int v){
		 if(v >= 0 && v < 4)
 			m_pakVertices[v].color = c;
		}
	private:
		ColorVertex* m_pakVertices;
	};
}
//--------------------------------------
#endif