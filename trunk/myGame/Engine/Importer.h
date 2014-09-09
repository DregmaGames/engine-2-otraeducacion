#ifndef IMPORTER_H
#define IMPORTER_H
#include "myEngine_API.h"
#include "Entity2D.h"
#include "tinyxml2.h"
#include "Scene.h"
#include "Sprite.h"

#include <string>
#include "RenderTypes.h"
#include <string>
//Singleton Class
namespace pGr{
	class Scene;
	class Renderer;
	class MYENGINE_API Importer
	{
		public:
		   Importer();
		   ~Importer();
		   bool init(Renderer*);
		   bool importScene(std::string xmlPath,pGr::Scene& m_Scene);
		private:
			Renderer* m_Renderer;
			bool importQuad (tinyxml2::XMLElement* quadNode, pGr::Scene&);
			bool importSprite (tinyxml2::XMLElement* spriteNode, pGr::Scene& m_Scene);
			bool importAnimation (tinyxml2::XMLElement* Elem, std::vector<Animation>** Anim);
	};
}
#endif//IMPORTER_H