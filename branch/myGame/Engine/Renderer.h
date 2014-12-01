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
		// --------------------------- 3D
		void draw(pGr::Primitive);
		void loadIdentity();
		void setCurrentVertexBuffer(pGr::VertexBuffer* m_VB);
		void setCurrentIndexBuffer(pGr::IndexBuffer* m_IB);
		VertexBuffer* CreateVB(size_t vSize, unsigned int FVF);
		IndexBuffer* CreateIB();
		// --------------------------- /3D
		void setTransformMatrix(D3DXMATRIX* kMatrix);
		void setMatrix(MatrixType, const Matrix&);
		void setCurrentTexture(const Texture& rkTexture);
		const Texture loadTexture(const std::string& rkFilename,int COLOR);
		const Texture loadTexture (const std::string& Fname);
		void setCameraPos(D3DXVECTOR3 Pos, D3DXVECTOR3 Look, D3DXVECTOR3 Up);
		void wireframe(bool wire);

		const Matrix& getProjectionMatrix() const;

		static Camera * m_pkCamera;
		IDirect3DDevice9* m_pkDevice;
		static Camera* getCamera();
	private:
		
		std::vector<pGr::Texture> m_akTextures;
		IDirect3D9* m_pkD3D;
		// Representa al hardware
		Matrix kProjectionMatrix;
		VertexBuffer* m_pkVertexbuffer;
		IndexBuffer* m_pkIndexBuffer;

		UINT r;
		UINT g;
		UINT b;
	};
}
#endif

//-----------------------------------------------