#pragma once
struct D3DXMATRIX;
struct D3DXVECTOR3;
struct D3DXPLANE;
#include "myEngine_API.h"
#include <math.h>
#include <limits>
#include <cstddef>
#include <iostream>

#include "../assimp/assimp/include/Importer.hpp"
#include "../assimp/assimp/include/scene.h"
#include "../assimp/assimp/include/postprocess.h"

namespace pGr
{

	typedef D3DXMATRIX* Matrix;
	typedef D3DXVECTOR3* Vector3;
	typedef D3DXPLANE* Plane;

	class MYENGINE_API MATHF
	{
		public:
			MATHF();
			~MATHF();
			static void eulerAnglesToQuaternion (float fRotX, float fRotY, float fRotZ,
								  float& orQX, float& orQY, float& orQZ, float& orQW);
			static void quaternionToEulerAngles (float qX, float qY, float qZ, float qW, 
								  float& orfRotX, float& orfRotY, float& orfRotZ);
	};

}