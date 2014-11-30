#include "Camera.h"
#include "Entity3D.h"
using namespace pGr;


Camera::Camera(IDirect3DDevice9 &device, Renderer* pkRenderer)
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
	for (UINT i = 0; i < 6; i++){
		FrustumBox[i] = new D3DXPLANE();
	}
	camera_device = &device;
	initCamera(pkRenderer);
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
void Camera::updateTransform(){
	/*para ver lo que es roll, pitch y yaw mira esta imágen o muerete.*/
	https://developer.valvesoftware.com/w/images/7/7e/Roll_pitch_yaw.gif
	/******************************************************************/

	D3DXMATRIX MatrixResult;

	D3DXMATRIX MatrixRoll;
	D3DXMATRIX MatrixPitch;
	D3DXMATRIX MatrixYaw;

	//crear una matriz por cada rotación.
	D3DXMatrixRotationAxis(&MatrixRoll, &camera_right, rx);
	D3DXMatrixRotationAxis(&MatrixPitch, &camera_target, ry);
	D3DXMatrixRotationAxis(&MatrixYaw, &camera_up, rz);

	//combinar las matrices en 1(MatrixResult).
	D3DXMatrixMultiply(&MatrixResult, &MatrixRoll,&MatrixPitch);
	D3DXMatrixMultiply(&MatrixResult, &MatrixYaw ,&MatrixResult);

	//transformar los vectores en la matriz.
	D3DXVec3TransformCoord(&camera_right,&camera_right,&MatrixResult);
	D3DXVec3TransformCoord(&camera_up,&camera_up,&MatrixResult);

	//con los otros vectores transformados a la matriz, saco el 3º vctor haciendo producto cruz.
	D3DXVec3Cross(&camera_target, &camera_right, &camera_up);

	//normalizamos los vectores.
	D3DXVec3Normalize(&camera_right,&camera_right);
	D3DXVec3Normalize(&camera_up,&camera_up);
	D3DXVec3Normalize(&camera_target,&camera_target);

	D3DXMatrixLookAtLH(&Camera_TransformMatrix,&camera_eye, &camera_target, &camera_up);
	camera_device->SetTransform(D3DTS_VIEW,&Camera_TransformMatrix);
	float fView41,fView42,fView43;
	fView41 = -D3DXVec3Dot(&camera_right, &camera_eye);
    fView42 = -D3DXVec3Dot(&camera_up, &camera_eye);
    fView43 = -D3DXVec3Dot(&camera_target, &camera_eye);


	D3DXMATRIX m_MatView(	camera_right.x,	camera_up.x,		camera_target.x,		0.0f,
							camera_right.y,	camera_up.y,		camera_target.y,		0.0f,
							camera_right.z,	camera_up.z,		camera_target.z,		0.0f,
							fView41,		fView42,			fView43,				1.0f);

    camera_device->SetTransform(D3DTS_VIEW,&m_MatView);

    rx = ry = rz = 0.0f;
	BuildFrustumBox();
}
void Camera::initCamera(Renderer* pkRenderer){
	m_pkRenderer = pkRenderer;
	D3DXMatrixLookAtLH(&Camera_TransformMatrix,&camera_eye, &camera_target, &camera_up);
	camera_device->SetTransform(D3DTS_VIEW,&Camera_TransformMatrix);
	walk(-20);
	fly(15);
	BuildFrustumBox();
}
void Camera::BuildFrustumBox(){
	std::cout << "Building Frustum Box -> Camera" << std::endl;
	D3DXMATRIX FrustunMatrix;
	D3DXMatrixMultiply(&FrustunMatrix, &Camera_TransformMatrix, m_pkRenderer->getProjectionMatrix());
	// left plane
	FrustumBox[0]->a = FrustunMatrix._14 + FrustunMatrix._11;
	FrustumBox[0]->b = FrustunMatrix._24 + FrustunMatrix._21;
	FrustumBox[0]->c = FrustunMatrix._34 + FrustunMatrix._31;
	FrustumBox[0]->d = FrustunMatrix._44 + FrustunMatrix._41;

	// right plane
	FrustumBox[1]->a = FrustunMatrix._14 - FrustunMatrix._11;
	FrustumBox[1]->b = FrustunMatrix._24 - FrustunMatrix._21;
	FrustumBox[1]->c = FrustunMatrix._34 - FrustunMatrix._31;
	FrustumBox[1]->d = FrustunMatrix._44 - FrustunMatrix._41;

	// top plane
	FrustumBox[2]->a = FrustunMatrix._14 - FrustunMatrix._12;
	FrustumBox[2]->b = FrustunMatrix._24 - FrustunMatrix._22;
	FrustumBox[2]->c = FrustunMatrix._34 - FrustunMatrix._32;
	FrustumBox[2]->d = FrustunMatrix._44 - FrustunMatrix._42;

	// bottom plane
	FrustumBox[3]->a = FrustunMatrix._14 + FrustunMatrix._12;
	FrustumBox[3]->b = FrustunMatrix._24 + FrustunMatrix._22;
	FrustumBox[3]->c = FrustunMatrix._34 + FrustunMatrix._32;
	FrustumBox[3]->d = FrustunMatrix._44 + FrustunMatrix._42;

	// near plane
	FrustumBox[4]->a = FrustunMatrix._13;
	FrustumBox[4]->b = FrustunMatrix._23;
	FrustumBox[4]->c = FrustunMatrix._33;
	FrustumBox[4]->d = FrustunMatrix._43;

	// far plane    
	FrustumBox[5]->a = FrustunMatrix._14 - FrustunMatrix._13;
	FrustumBox[5]->b = FrustunMatrix._24 - FrustunMatrix._23;
	FrustumBox[5]->c = FrustunMatrix._34 - FrustunMatrix._33;
	FrustumBox[5]->d = FrustunMatrix._44 - FrustunMatrix._43;

	// normalize planes
	for (UINT i = 0; i<6; i++){
		D3DXPlaneNormalize(FrustumBox[i], FrustumBox[i]);
	}
}
int Camera::AABBinFrustum(Entity3D& pkNode)
{
	AABB& b = pkNode.getAABB();

	D3DXVECTOR3 aabbSize = D3DXVECTOR3(b.width(), b.height(), b.depth());
	D3DXVECTOR3 aabbCenter = D3DXVECTOR3(b.offset()->x + pkNode.transformationMatrix()->_41, 
		b.offset()->y + pkNode.transformationMatrix()->_42, b.offset()->z + pkNode.transformationMatrix()->_43);

	int result = INSIDE;
	for (int i = 0; i < 6; i++){
		Plane frustumPlane = FrustumBox[i];
		float d = aabbCenter.x * frustumPlane->a +
			aabbCenter.y * frustumPlane->b +
			aabbCenter.z * frustumPlane->c;

		float r = aabbSize.x * std::abs(frustumPlane->a) +
			aabbSize.y * std::abs(frustumPlane->b) +
			aabbSize.z * std::abs(frustumPlane->c);

		float d_p_r = d + r;
		float d_m_r = d - r;

		if (d_p_r < -frustumPlane->d){
			std::cout<<"OUTSIDE"<<std::endl;
			result = OUTSIDE;
			break;
		}
		else if (d_m_r < -frustumPlane->d){
			std::cout<<"INTERSECT"<<std::endl;
			result = INTERSECT;
		}
	}
	return result;
}
