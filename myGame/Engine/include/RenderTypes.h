#ifndef RENDERTYPES_H
#define RENDERTYPES_H
//--------------------------------------

#include <Windows.h>
#include "myEngine_API.h"
#include "Mathjavi.h"
#include <d3d9.h>

//--------------------------------------
namespace pGr{
	struct MYENGINE_API ColorVertex
	{
		//Guarda las coordenadas del vertice
		float x; 
		float y;
		float z;

		DWORD color; // Guarda el vertex Format
	};
	extern const int ColorVertexType;

	struct MYENGINE_API TextureCoordVertex{
		float x;
		float y;
		float z;

		float u;
		float V;
	};
	extern const int TextureCoordVertexType;
	//--------------------------------------

	typedef IDirect3DTexture9* Texture;
	static const Texture NoTexture = NULL;

	//--------------------------------------
	//primitivas
	enum Primitive
	{
		TriangleList= 0,
		TriangleStrip,
		PointList,
		LineList,
		LineStrip,
		TriangleFan,
		PrimitiveCount
	};
	enum MatrixType{
		View = 0,
		Projection,
		World,
		MatrixTypeCount
	};
	//--------------------------------------
	// build an unsigned int from color ( see d3dColor_XRGB)
#define PG1_COLOR_ARGB(a,r,g,b)  ((DWORD)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
#define PG1_COLOR_RGB(r,g,b) PG1_COLOR_ARGB(0xff,r,g,b)

}
//endif RENDERTYPES.H
#endif
//--------------------------------------