
//---------------------------------------------------------------------------
#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H
//---------------------------------------------------------------------------
#include "myEngine_API.h"
//---------------------------------------------------------------------------
//Includes necesarios para Direct3D
#include <d3d9.h>
#include <d3dx9.h>
#include <cassert>
//---------------------------------------------------------------------------
namespace pGr
{
	//---------------------------------------------------------------------------
	class Renderer;
	//---------------------------------------------------------------------------
	class MYENGINE_API VertexBuffer
	{
	public:
		VertexBuffer (IDirect3DDevice9* pkDevice, size_t uiVertexSize, unsigned int uiFVF);
		~VertexBuffer ();

		bool create ();
		//Este método le indicará cual es el vb activo a DirectX.
		void bind ();
		//Este método invocará a DrawPrimitive (método de DirectX que procesa los vértices insertos en el vb).
		//Será invocado al menos una vez en el dibujado de cada objeto (y más si la cantidad de vértices del objeto es mayor a m_uiFlush).
		void flush ();
		//método transferir vértices al vb. Se le pasa como parámetro el array de vértices, 
		//la primitiva a dibujar y la cantidad de vértices en el array.
		void draw (const void* pvVertices, D3DPRIMITIVETYPE ePrimitiveType, unsigned int uiVertexCount);
		//Libera al vertex buffer. Usualmente este método se invocará en el apagado del juego.
		void release ();

	private:

		// Tamaño de Vertex Buffer
		static const unsigned int SIZE = 400;
		static const unsigned int FLUSH_COUNT = 200;

		unsigned int m_uiBase; //Indica el índice en el cual se deja el vertex buffer
		unsigned int m_uiVertexToLock; //Indica la cantidad de vértices a trabar en Draw
		unsigned int m_uiVertexSize; //Indica el tamaño del vertex buffer. Fijado a un valor constante
		unsigned int m_uiFVF;

		D3DPRIMITIVETYPE m_ePrimitiveType; //Indica la primitiva pasada como parámetro a Draw
		LPDIRECT3DVERTEXBUFFER9 m_pkVertexBuffer; //El Vértex Buffer creado queda encapsulado dentro de la clase
		IDirect3DDevice9 * m_pkDevice; //Almaceno temporalmente el dispositivo pasado como parámetro en Draw.
	};
	//---------------------------------------------------------------------------
} 
//---------------------------------------------------------------------------
#endif  // VERTEXBUFFER_H
//---------------------------------------------------------------------------
