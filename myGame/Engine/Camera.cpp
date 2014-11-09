#include "Camera.h"
#include "Renderer.h"

#include<sstream>
using namespace pGr;

Camera::Camera(IDirect3DDevice9 &device)
	:
	Camera_TransformMatrix(),
	camera_eye		(0.0f, 0.0f, 0.0f),
	camera_target	(0.0f, 0.0f, 1.0f),
	camera_up		(0.0f, 1.0f, 0.0f),
	camera_right	(1.0f, 0.0f, 0.0f),
	rx(0),
	ry(0),
	rz(0)
{
	camera_device = &device;
	initCamera();
}
Camera::~Camera(){
}
void Camera::fly(float distance){
	camera_eye += distance*camera_up;
	updateTransform();
}
void Camera::strafe(float distance){
	camera_eye += distance*camera_right;
	updateTransform();
}
void Camera::walk(float distance){
	camera_eye += distance*camera_target;
	updateTransform();
}
void Camera::yaw(float angle){
	rx+=angle;
	updateTransform();
}
void Camera::pitch(float angle){
	ry+=angle;
	updateTransform();
}
void Camera::roll(float angle){
	rz+=angle;
	updateTransform();
}

//ARREGLAAAR!!!!
void Camera::updateTransform(){
	/*
	para ver lo que es roll, pitch y yaw mira esta imágen o muere.
	https://developer.valvesoftware.com/w/images/7/7e/Roll_pitch_yaw.gif
	*/
	D3DXMATRIX MatrixResult;
	D3DXMATRIX MatrixRoll;
	D3DXMATRIX MatrixPitch;
	D3DXMATRIX MatrixYaw;
	//crear una matriz por cada rotación.
	D3DXMatrixRotationAxis(&MatrixRoll, &camera_right, rx);
	D3DXMatrixRotationAxis(&MatrixPitch, &camera_target, ry);
	D3DXMatrixRotationAxis(&MatrixYaw, &camera_up, rz);
	//combinar las matrices en 1.
	D3DXMatrixMultiply(&MatrixResult, &MatrixRoll,&MatrixPitch);
	D3DXMatrixMultiply(&MatrixResult, &MatrixYaw ,&MatrixResult);
	//transformar los vectores en la matriz.
	D3DXVec3TransformCoord(&camera_right,&camera_right,&MatrixResult);
	D3DXVec3TransformCoord(&camera_up,&camera_up,&MatrixResult);
	//con los otros vectores transformados a la matriz, saco el 3º vctor haciendo
	//producto cruz.
	D3DXVec3Cross(&camera_target, &camera_right, &camera_up);
	//normalize vectors
	D3DXVec3Normalize(&camera_right,&camera_right);
	D3DXVec3Normalize(&camera_up,&camera_up);
	D3DXVec3Normalize(&camera_target,&camera_target);

	D3DXMatrixLookAtLH(&Camera_TransformMatrix,&camera_eye, &camera_target, &camera_up);
	camera_device->SetTransform(D3DTS_VIEW,&Camera_TransformMatrix);
	float fView41,fView42,fView43;
	fView41 = -D3DXVec3Dot(&camera_right, &camera_eye);
    fView42 = -D3DXVec3Dot(&camera_up, &camera_eye);
    fView43 = -D3DXVec3Dot(&camera_target, &camera_eye);
    //Fill in the view matrix
    D3DXMATRIX m_MatView(	camera_right.x,	camera_up.x,		camera_target.x,		0.0f,
							camera_right.y,	camera_up.y,		camera_target.y,		0.0f,
							camera_right.z,	camera_up.z,		camera_target.z,		0.0f,
							fView41,		fView42,			fView43,				1.0f);

    //Set view transform
    camera_device->SetTransform(D3DTS_VIEW,&m_MatView);
    //Reset update members
    rx = ry = rz = 0.0f;
}
void Camera::initCamera(){
	D3DXMatrixLookAtLH(&Camera_TransformMatrix,&camera_eye, &camera_target, &camera_up);
	camera_device->SetTransform(D3DTS_VIEW,&Camera_TransformMatrix);
	walk(-20);
	fly(15);
}
void Camera::DebugCamPos(){
	
	//OutputDebugString("z");
	//std::string a= "datos: "+ camera_eye.x +"cueck"+(int)camera_eye.y +"cueck"+(int)camera_eye.z;
}