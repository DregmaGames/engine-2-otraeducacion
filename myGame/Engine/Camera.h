#pragma once
#include "myEngine_API.h"
#include "Renderer.h"
#include "Mathjavi.h"
#include <string>
namespace pGr
{
	class MYENGINE_API Camera
	{
		public:

			Camera(IDirect3DDevice9& device);
			~Camera();

			void updateTransform();
			void initCamera();
			void DebugCamPos();

			void yaw(float angle);
			void roll(float angle);
			void pitch(float angle);

			void fly(float dist);
			void walk(float dist);
			void strafe(float dist);

		private:

			float rx,ry,rz;

			D3DXVECTOR3 camera_eye;
			D3DXVECTOR3 camera_target;
			D3DXVECTOR3 camera_up;
			D3DXVECTOR3 camera_right;
			D3DXMATRIX Camera_TransformMatrix;
			IDirect3DDevice9* camera_device;
	};
}