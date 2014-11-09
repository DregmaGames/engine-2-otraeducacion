#include "Sprite.h"
#include "Renderer.h"
#include <d3dx9.h>
using namespace pGr;
Sprite::Sprite()
	:
	Entity3D(),
	m_kTexture(NoTexture),/*el NoTexture lo hace mas claro que ponerle NULL, en si NoTexture es igual a un NULL*/
	m_pakVertex(new TextureCoordVertex[4])
{
	m_pakVertex[0].x = -0.5; m_pakVertex[0].y = 0.5; m_pakVertex[0].z = 0;
	m_pakVertex[1].x = 0.5; m_pakVertex[1].y = 0.5; m_pakVertex[1].z = 0;
	m_pakVertex[2].x = -0.5; m_pakVertex[2].y = -0.5; m_pakVertex[2].z = 0;
	m_pakVertex[3].x = 0.5; m_pakVertex[3].y = -0.5; m_pakVertex[3].z = 0;
	//coordenadas de la textura.
	m_pakVertex[0].u = 0.0; m_pakVertex[0].V=0.0;
	m_pakVertex[1].u = 1.0; m_pakVertex[1].V=0.0;
	m_pakVertex[2].u = 0.0; m_pakVertex[2].V=1.0;
	m_pakVertex[3].u = 1.0; m_pakVertex[3].V=1.0;
}

Sprite::~Sprite(){
	delete[] m_pakVertex;
	m_pakVertex = NULL;
}
void Sprite::setTextureCoords(	float fU1, float fV1,
								float fU2, float fV2,
								float fU3, float fV3,
								float fU4, float fV4)
{
	m_pakVertex[0].u = fU1; m_pakVertex[0].V = fV1;
	m_pakVertex[1].u = fU2; m_pakVertex[1].V = fV2;
	m_pakVertex[2].u = fU3; m_pakVertex[2].V = fV3;
	m_pakVertex[3].u = fU4; m_pakVertex[3].V = fV4;
}
void Sprite::setTexture(Texture& rkTexture){
	m_kTexture=rkTexture;
}
void Sprite::Update(Timer& rkTimer){
	if(!m_pkAnimation){
		return;
	}
	m_pkAnimation->update(rkTimer);
	unsigned int ui_CurrentFrame= m_pkAnimation->currentFrame();

	if(ui_CurrentFrame!= m_uiPreviousFrame)
	{
		const Animation::Frame& rkFrame= m_pkAnimation->frames()[ui_CurrentFrame];
			setTextureCoords(rkFrame.u1,rkFrame.v1, rkFrame.u2,rkFrame.v2,
							rkFrame.u3,rkFrame.v3, rkFrame.u4,rkFrame.v4);
	}
}

void Sprite::draw(Renderer& rkRenderer){
	rkRenderer.setCurrentTexture(m_kTexture);
	rkRenderer.setMatrix(World, m_pkTransformationMatrix);
	
	rkRenderer.draw(m_pakVertex,pGr::TriangleStrip, 4);
}

void Sprite::setAnimation(Animation* anim){
	m_pkAnimation = anim;
}

void Sprite::setAnimation(std::string Name){
	for(int i=0;i<animation_List.size();i++){
		if(animation_List[i].getName()==Name){
			m_pkAnimation = &animation_List[i];
			return;
		}
	}
	/*for (std::list<pGr::Animation>::iterator it = animation_List.begin(); it != animation_List.end(); it++){
		if(it._Ptr->_Myval->getName() == Name){
			m_pkAnimation = *it;
			return;
		}
	}*/
}
void Sprite::addAnimation(std::vector<Animation> AnimVector){
	animation_List = AnimVector;
	m_pkAnimation = &animation_List[0];
}
