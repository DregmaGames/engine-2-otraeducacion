#include "Camera.h"
#include "Renderer.h"
using namespace pGr;

Camera::Camera(IDirect3DDevice9 &device)
{
	camera_device = &device;
	Camera_TransformMatrix = new D3DXMATRIX();
	camera_eye = new D3DXVECTOR3(0.0f, 0.0f,-1000.0f);
	camera_target = new D3DXVECTOR3(0.0f, 0.0f, -999.0f);
	camera_up = new D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	px,py,pz,rx,ry,rz = 0.0f;
	pz = -1000.0f;
	initCamera();
}
Camera::~Camera(){
	camera_eye = NULL;
	camera_target = NULL;
	camera_up = NULL;
	Camera_TransformMatrix=NULL;
	delete camera_eye;
	delete camera_target;
	delete camera_up;
	delete Camera_TransformMatrix;
}
void Camera::zoom(float zoom){

}
void Camera::fly(float distance){
	D3DXMATRIX aux;
	D3DXMatrixTranslation(&aux,0,distance,0);
	//D3DXMatrixMultiply(Camera_TransformMatrix,&aux,Camera_TransformMatrix);
	camera_device->MultiplyTransform(D3DTS_VIEW,&aux);
}
void Camera::strafe(float distance){
	D3DXMATRIX aux;
	D3DXMatrixTranslation(&aux,distance,0,0);
	camera_device->MultiplyTransform(D3DTS_VIEW,&aux);
}
void Camera::walk(float distance){
	D3DXMATRIX aux;
	D3DXMatrixTranslation(&aux,0,0,distance);
	camera_device->MultiplyTransform(D3DTS_VIEW,&aux);
}
void Camera::yaw(float angle){
	ry+=angle;
	D3DXMATRIX aux;
	D3DXMatrixRotationY(&aux,D3DXToRadian(angle));
	camera_device->MultiplyTransform(D3DTS_VIEW,&aux);
}
void Camera::pitch(float angle){
	rz+=angle;
	D3DXMATRIX aux;
	D3DXMatrixRotationZ(&aux,D3DXToRadian(angle));
	camera_device->MultiplyTransform(D3DTS_VIEW,&aux);
}
void Camera::roll(float angle){
	rx+=angle;
	D3DXMATRIX aux;
	D3DXMatrixRotationX(&aux,D3DXToRadian(angle));
	camera_device->MultiplyTransform(D3DTS_VIEW,&aux);
}
void Camera::updateTransform(){
	/*D3DXMATRIX aux;
	camera_device->GetTransform(D3DTS_VIEW,&aux);
	D3DXVECTOR3 scale;
	D3DXQUATERNION rotation;
	D3DXVECTOR3 position;
	D3DXMatrixDecompose(&scale,&rotation,&position,*/
}
void Camera::initCamera(){
	D3DXMatrixLookAtLH(Camera_TransformMatrix,camera_eye, camera_target, camera_up);
	camera_device->SetTransform(D3DTS_VIEW,Camera_TransformMatrix);
}