#pragma once

#include "myEngine_API.h"
#include "Mathjavi.h"

namespace pGr
{
	class AABB
	{
	public:
		AABB();
		~AABB();

		float width()	const;
		float height()	const;
		float depth()	const;

		const Vector3& offset() const;
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