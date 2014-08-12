#include "Camera.h"
#include "Renderer.h"
using namespace pGr;

Camera::Camera(IDirect3DDevice9 &device)
{
	camera_device = &device;
	camera_eye = new D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	camera_target = new D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	camera_up = new D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}
Camera::~Camera(){
	camera_eye = NULL;
	camera_target = NULL;
	camera_up = NULL;
	delete camera_eye;
	delete camera_target;
	delete camera_up;
}
void Camera::fly(float distance){
	camera_eye->y += distance;
	camera_target->y += distance;
	updateTransform();
}
void Camera::strafe(float distance){

}
void Camera::walk(float distance){

}
void Camera::yaw(float angle){

}
void Camera::pitch(float angle){

}
void Camera::roll(float angle){

}
void Camera::updateTransform(){
	D3DXMATRIX Camera_TransformMatrix;
	D3DXMatrixLookAtLH(&Camera_TransformMatrix,camera_eye, camera_target, camera_up);
	camera_device->SetTransform(D3DTS_VIEW,&Camera_TransformMatrix);
}