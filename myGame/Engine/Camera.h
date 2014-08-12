#pragma once
#include "myEngine_API.h"
#include "Renderer.h"
#include "Mathjavi.h"
namespace pGr{
	class MYENGINE_API Camera{
	public:
		Camera(IDirect3DDevice9& device);
		~Camera();

		void updateTransform();

		void yaw(float angle);
		void roll(float angle);
		void pitch(float angle);

		void fly(float dist);
		void walk(float dist);
		void strafe(float dist);
	private:
		D3DXVECTOR3* camera_eye;
		D3DXVECTOR3* camera_target;
		D3DXVECTOR3* camera_up;
		IDirect3DDevice9* camera_device;
	};
}