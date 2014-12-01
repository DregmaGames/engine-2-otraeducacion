#ifndef SPRITE_H
#define SPRITE_H
#include "myEngine_API.h"
#include "RenderTypes.h"
#include "Entity3D.h"
#include "Renderer.h"
#include "Animation.h"
#include "pg1_timer.h"
#include <vector>
#include <string>
namespace pGr{
	class MYENGINE_API Sprite:public Entity3D
	{
	public:
		Sprite();
		~Sprite();
	public:
		void setTexture(Texture& rkTexture);
		void setTextureCoords(	float fU1, float fV1, 
								float fU2, float fV2,
								float fU3, float fV3, 
								float fU4, float fV4
		);
		void draw(Renderer& rkRenderer);
	public: 
			void addAnimation(std::vector<Animation> AnimVector);
			void setAnimation(Animation* m_pkAnimation);
			void setAnimation(std::string Name);
			void Update(Timer& rkTimer);
	private:

		std::vector<pGr::Animation> animation_List;
		pGr::Animation* m_pkAnimation;
		unsigned int m_uiPreviousFrame;
		Texture m_kTexture;
		TextureCoordVertex* m_pakVertex;
	};
}
#endif