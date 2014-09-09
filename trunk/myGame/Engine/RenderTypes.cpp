#include "RenderTypes.h"
// include DirectX to have the matrix constants
#include <d3dx9.h>
// color vertex D3D define
const int pGr::ColorVertexType = (D3DFVF_XYZ | D3DFVF_DIFFUSE);
const int pGr::TextureCoordVertexType = (D3DFVF_XYZ | D3DFVF_TEX1);