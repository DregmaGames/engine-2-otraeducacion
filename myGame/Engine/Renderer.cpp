#include "Renderer.h"
#include "Mathjavi.h"
#include "Camera.h"


//-----------------------------------------------
using namespace pGr;
Camera* Renderer::m_pkCamera = NULL;

D3DPRIMITIVETYPE primitivesMapping[pGr::PrimitiveCount] =
{
	D3DPT_TRIANGLELIST,
	D3DPT_TRIANGLESTRIP,
	D3DPT_POINTLIST,
	D3DPT_LINELIST,
	D3DPT_LINESTRIP,
	D3DPT_TRIANGLEFAN
};

D3DTRANSFORMSTATETYPE g_eMatrixTypeMapping[MatrixTypeCount] =
{
	D3DTS_VIEW,
	D3DTS_PROJECTION,
	D3DTS_WORLD
};

Renderer::Renderer() :
m_pkD3D(NULL),
m_pkDevice(NULL),
m_pkVertexBuffer(NULL),
m_pkIndexBuffer(NULL),
kProjectionMatrix(new D3DXMATRIX())
{

}
//-----------------------------------------------
Renderer::~Renderer(){
	if (m_pkD3D){
		m_pkD3D->Release();
		m_pkD3D = NULL;
	}
	if (m_pkDevice){
		m_pkDevice->Release();
		m_pkDevice = NULL;
	}
	//borrar texturas
	for (std::vector<Texture>::iterator it = m_akTextures.begin(); it != m_akTextures.end(); it++)
	{
		(*it)->Release();
		(*it) = NULL;
	}
	m_akTextures.clear();
}
//-----------------------------------------------
bool Renderer::init(HWND hWnd){
	m_pkD3D = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d;
	ZeroMemory(&d, sizeof(d));
	d.Windowed = TRUE;
	d.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d.hDeviceWindow = hWnd;
	d.EnableAutoDepthStencil = TRUE;
	d.AutoDepthStencilFormat = D3DFMT_D16;
	d.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	if (m_pkD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d,
		&m_pkDevice)
		== D3D_OK)
	{
		m_pkDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		m_pkDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		//m_pkDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME); //renderiza en ireframe.

		m_pkDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_pkDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		m_pkDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_pkDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		m_pkDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

		D3DVIEWPORT9 kViewport;
		m_pkDevice->GetViewport(&kViewport);

		float fViewportWidth = static_cast<float>(kViewport.Width);
		float fViewportHeight = static_cast<float>(kViewport.Height);

		//D3DXMATRIX kProjectionMatrix;
		D3DXMatrixPerspectiveFovLH(kProjectionMatrix, D3DXToRadian(90), fViewportWidth / fViewportHeight, 0.1f, 1000);

		m_pkDevice->SetTransform(D3DTS_PROJECTION, kProjectionMatrix);

		m_pkCamera = new Camera(*m_pkDevice, (Renderer*)this);
		return true;
	}
	return false;
}
void Renderer::setCameraPos(D3DXVECTOR3 Pos, D3DXVECTOR3 Look, D3DXVECTOR3 Up){
	D3DXMATRIX C_TransformMatrix;
	D3DXMatrixLookAtLH(&C_TransformMatrix, &Pos, &Look, &Up);
	m_pkDevice->SetTransform(D3DTS_VIEW, &C_TransformMatrix);
}
//-----------------------------------------------
void Renderer::beginFrame(){
	// Limpia la escena
	m_pkDevice->Clear(0,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(100, 100, 100),	//COLOr escena
		1.0f,
		0);
	// Comienzo el render de una escena
	m_pkDevice->BeginScene();
}
//-----------------------------------------------
void Renderer::endFrame(){
	// Termina 
	m_pkDevice->EndScene();
	m_pkDevice->Present(NULL,
		NULL,
		NULL,
		NULL);

}
void Renderer::setMatrix(MatrixType eMatrixType, const Matrix& rkMatrix)
{
	m_pkDevice->SetTransform(g_eMatrixTypeMapping[eMatrixType], rkMatrix);
}

const Matrix&	Renderer::getProjectionMatrix() const{
	return kProjectionMatrix;
}
const Texture Renderer::loadTexture(const std::string& rkFilename, int iColorKey)
{
	IDirect3DTexture9* pkTexture = NULL;
	HRESULT hr = D3DXCreateTextureFromFileEx(
		m_pkDevice,
		rkFilename.c_str(),
		0, 0, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE,
		iColorKey,
		NULL,
		NULL,
		&pkTexture
		);

	if (hr != D3D_OK){
		return NoTexture;
	}
	else{
		m_akTextures.push_back(pkTexture);
		return pkTexture;
	}

}

const Texture Renderer::loadTexture(const std::string& Fname)
{
	IDirect3DTexture9* p_Texture = NULL;
	HRESULT HR = D3DXCreateTextureFromFileEx(m_pkDevice,
		Fname.c_str(),
		0, 0, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE,
		0,
		NULL,
		NULL,
		&p_Texture);
	if (HR != D3D_OK)
	{
		return NoTexture;
	}
	else
	{
		m_akTextures.push_back(p_Texture);
		return p_Texture;
	}
}

void Renderer::setCurrentTexture(const Texture& rkTexture)
{
	m_pkDevice->SetTexture(0, rkTexture);//el 0 es para especificar si es normalmap, difuse, specular, etc;
}

// ----------------------------------------------------------- 3D
void Renderer::draw(pGr::Primitive thePrimitive)
{
	int iPrimitiveCount = 0;

	D3DPRIMITIVETYPE ePrimitiveType = primitivesMapping[thePrimitive];

	if (ePrimitiveType == D3DPT_POINTLIST)
	{
		iPrimitiveCount = m_pkIndexBuffer->indexCount();
	}
	else if (ePrimitiveType == D3DPT_LINELIST)
	{
		iPrimitiveCount = m_pkIndexBuffer->indexCount() / 2;
	}
	else if (ePrimitiveType == D3DPT_LINESTRIP)
	{
		iPrimitiveCount = m_pkIndexBuffer->indexCount() - 1;
	}
	else if (ePrimitiveType == D3DPT_TRIANGLELIST)
	{
		iPrimitiveCount = m_pkIndexBuffer->indexCount() / 3;
	}
	else if (ePrimitiveType == D3DPT_TRIANGLESTRIP)
	{
		iPrimitiveCount = m_pkIndexBuffer->indexCount() - 2;
	}
	else if (ePrimitiveType == D3DPT_TRIANGLEFAN)
	{
		iPrimitiveCount = m_pkIndexBuffer->indexCount() - 2;
	}

	m_pkDevice->DrawIndexedPrimitive(primitivesMapping[thePrimitive], 0, 0, m_pkVertexBuffer->vertexCount(), 0, iPrimitiveCount);
}

void Renderer::setCurrentVertexBuffer(VertexBuffer* theVB)
{
	m_pkVertexBuffer = theVB;
}

void Renderer::setCurrentIndexBuffer(IndexBuffer* theIB)
{
	m_pkIndexBuffer = theIB;
}

VertexBuffer* Renderer::CreateVB(size_t vSize, unsigned int FVF)
{
	return new VertexBuffer(*this, m_pkDevice, vSize, FVF);
}

IndexBuffer* Renderer::CreateIB()
{
	return new IndexBuffer(*this, m_pkDevice);

}

void Renderer::wireframe(bool wire){
	if (wire){
		m_pkDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME); //renderiza en wireframe.	
	}
	else
	{
		m_pkDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID); //renderiza en solid.	
	}
}

Camera* Renderer::getCamera()
{
	return m_pkCamera;
}
void Renderer::loadIdentity(){
	D3DXMATRIX kTempMatrix;

	// set identity matrix
	D3DXMatrixIdentity(&kTempMatrix);

	// if it is a view matrix, use default values


	D3DXVECTOR3 kEyePos(0, 0, -1);
	D3DXVECTOR3 kLookPos(0, 0, 0);
	D3DXVECTOR3 kUpVector(0, 1, 0);

	// generate the view matrix
	D3DXMatrixLookAtLH(&kTempMatrix, &kEyePos, &kLookPos, &kUpVector);

	// set the matrix
	m_pkDevice->SetTransform(D3DTS_VIEW, &kTempMatrix);
}
void Renderer::setTransformMatrix(D3DXMATRIX* kMatrix){
	// set the matrix
	m_pkDevice->MultiplyTransform(D3DTS_VIEW, kMatrix);
}
// -----------------------------------------------------------/3D