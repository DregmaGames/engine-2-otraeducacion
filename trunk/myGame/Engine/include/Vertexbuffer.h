
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
		//Este m�todo le indicar� cual es el vb activo a DirectX.
		void bind ();
		//Este m�todo invocar� a DrawPrimitive (m�todo de DirectX que procesa los v�rtices insertos en el vb).
		//Ser� invocado al menos una vez en el dibujado de cada objeto (y m�s si la cantidad de v�rtices del objeto es mayor a m_uiFlush).
		void flush ();
		//m�todo transferir v�rtices al vb. Se le pasa como par�metro el array de v�rtices, 
		//la primitiva a dibujar y la cantidad de v�rtices en el array.
		void draw (const void* pvVertices, D3DPRIMITIVETYPE ePrimitiveType, unsigned int uiVertexCount);
		//Libera al vertex buffer. Usualmente este m�todo se invocar� en el apagado del juego.
		void release ();

	private:

		// Tama�o de Vertex Buffer
		static const unsigned int SIZE = 400;
		static const unsigned int FLUSH_COUNT = 200;

		unsigned int m_uiBase; //Indica el �ndice en el cual se deja el vertex buffer
		unsigned int m_uiVertexToLock; //Indica la cantidad de v�rtices a trabar en Draw
		unsigned int m_uiVertexSize; //Indica el tama�o del vertex buffer. Fijado a un valor constante
		unsigned int m_uiFVF;

		D3DPRIMITIVETYPE m_ePrimitiveType; //Indica la primitiva pasada como par�metro a Draw
		LPDIRECT3DVERTEXBUFFER9 m_pkVertexBuffer; //El V�rtex Buffer creado queda encapsulado dentro de la clase
		IDirect3DDevice9 * m_pkDevice; //Almaceno temporalmente el dispositivo pasado como par�metro en Draw.
	};
	//---------------------------------------------------------------------------
} 
//---------------------------------------------------------------------------
#endif  // VERTEXBUFFER_H
//---------------------------------------------------------------------------
