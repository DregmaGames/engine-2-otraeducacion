#ifndef RENDERER_H
#define RENDERER_H
#include <d3d9.h>
#include "myengine_api.h"
#include "pg2_vertexbuffer.h"
#include "pg2_indexbuffer.h"
#include "RenderTypes.h"
#include "Mathjavi.h"
#include <windows.h>
#include <string.h>
#include <vector>
#include "Camera.h"
//---------------------------------------

namespace pGr
{
	class Camera;
	class MYENGINE_API Renderer{
		//--Initializacion
	public:
		Renderer();
		~Renderer();
		bool init (HWND hWnd);
		//rendering
	public:
		void beginFrame();
		void endFrame();
		void draw(ColorVertex* apkVertices, Primitive ePrimitive,size_t vertexCount);
		void draw(TextureCoordVertex* apkVertex, Primitive ePrimitive, size_t vertexCount);
		// --------------------------- 3D
		void draw(pGr::Primitive&);
		void setCurrentVertexBuffer(pGr::VertexBuffer* m_VB);
		void setCurrentIndexBuffer(pGr::IndexBuffer* m_IB);
		VertexBuffer* CreateVB(size_t vSize, unsigned int FVF);
		IndexBuffer* CreateIB();
		// --------------------------- /3D
		void setMatrix(MatrixType eMatrixType,const Matrix& );
		void setCurrentTexture(const Texture& rkTexture);
		const Texture loadTexture(const std::string& rkFilename,int COLOR);
		void setCameraPos(D3DXVECTOR3 Pos, D3DXVECTOR3 Look, D3DXVECTOR3 Up);

		Camera * m_pkCamera;
	private:
		//VertexBuffer* m_pkColorVB;
		//VertexBuffer* m_pkTextureCoordVB;
		
		//directx stuff
	private:
		std::vector<pGr::Texture> m_akTextures;
		IDirect3D9 *m_pkD3D;
		// Representa al hardware
		
		IDirect3DDevice9* m_pkDevice;

		VertexBuffer* m_pkVertexbuffer;
		IndexBuffer* m_pkIndexBuffer;

		Renderer* m_rkRenderer;

		UINT r;
		UINT g;
		UINT b;
	};
}
#endif

//-----------------------------------------------