#pragma once
#include "myEngine_API.h"
#include "Renderer.h"
#include "Mathjavi.h"

#include <string>
#include <iostream>
namespace pGr
{
	class MATHJAVI;
	class Entity3D;
	class MYENGINE_API Camera
	{
		protected:
			/*creamos los 6 pñanos del frustum, adelante, atras, arriba abajo, izquierda, derecha, en el orto*/
			Plane FrustumBox[6];
			void BuildFrustumBox();
			Renderer* m_pkRenderer;
			

		public:
			Camera(IDirect3DDevice9& device, Renderer* pkRenderer);
			~Camera();

			static enum { OUTSIDE, INTERSECT, INSIDE };

			int AABBinFrustum(Entity3D&);

			void updateTransform();
			void initCamera(Renderer* pkRenderer);

			void yaw(float angle);
			void roll(float angle);
			void pitch(float angle);

			void fly(float dist);
			void walk(float dist);
			void strafe(float dist);
			

		private:

			float rx,ry,rz;

			D3DXVECTOR3 camera_eye;//pos eye
			D3DXVECTOR3 camera_target;//pos target
			D3DXVECTOR3 camera_up;//vector up
			D3DXVECTOR3 camera_right;//vector right

			D3DXMATRIX Camera_TransformMatrix;//transform

			IDirect3DDevice9* camera_device;//device
	};
}