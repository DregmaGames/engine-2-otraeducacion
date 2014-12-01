#pragma once

#include "myEngine_API.h"

struct D3DXVECTOR3;
struct D3DXMATRIX;
struct D3DXPLANE;

namespace pGr
{
	typedef D3DXPLANE* Plane;
	typedef D3DXMATRIX* Matrix;
	typedef D3DXVECTOR3* Vector3;

	class AABB
	{
		public:

			AABB();
			~AABB();

			float width()	const;
			float height()	const;
			float depth()	const;

			const Vector3& offset () const;
			const Vector3* corners() const;
			void setDataAABB(float fWidth, float fHeight, float fDepth, float fOffsetX, float fOffsetY, float fOffsetZ);
			
		private:

			Vector3	m_pkOffset;
			Vector3	m_pkCorners[8];

			float m_fWidth;
			float m_fDepth;
			float m_fHeight;
			
	};
}