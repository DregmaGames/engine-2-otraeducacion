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
		void initCamera();

		void yaw(float angle);
		void roll(float angle);
		void pitch(float angle);

		void fly(float dist);
		void walk(float dist);
		void strafe(float dist);
		void zoom(float zoom);

	private:
		float rx,ry,rz;
		float px,py,pz;
		D3DXVECTOR3* camera_eye;
		D3DXVECTOR3* camera_target;
		D3DXVECTOR3* camera_up;
		D3DXMATRIX* Camera_TransformMatrix;
		IDirect3DDevice9* camera_device;
	};
}