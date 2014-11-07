#ifndef IMPORTER_H
#define IMPORTER_H

#include "myEngine_API.h"
#include <map>
#include <list>
#include <vector>
#include <string>
#include "tinyxml2.h"
#include "RenderTypes.h"

//Singleton Class

// Assimp
struct aiNode;
struct aiMesh;
struct aiMaterial;
struct aiScene;
#pragma comment(lib, "../assimp/assimp/lib/assimp.lib")

namespace pGr{

	class Mesh;
	class Node;
	class Quad;
	class Scene;
	class Sprite;
	class Renderer;
	class Animation;

	class MYENGINE_API Importer
	{
		friend class Engine;
		public:
		   
			bool init(Renderer*);
			bool importScene(std::string xmlPath,pGr::Scene& m_Scene);

			// 3D things
			Importer* getInstance();
			void importMesh(Mesh&, std::string);
			Renderer& getRenderer() const{ return *m_Renderer; }
			bool import3DScene(const std::string& fileName, Node& node);
		  
		protected:

			Importer();
			~Importer();

		private:

			Renderer* m_Renderer;
			static Importer* Instance;
				
			bool importNode(const aiNode* pkAiNode, const aiScene* pkAiScene, Node& node);
			bool importMesh(const aiMesh* pkAiMesh, const aiMaterial* pkAiMaterial, Mesh& mesh);
			void quaternionToEulerAngles (float qX, float qY, float qZ, float qW, 
								  float& orfRotX, float& orfRotY, float& orfRotZ);

			//OLD THINGS IMPORTER 2D
			bool importQuad (tinyxml2::XMLElement* quadNode, pGr::Scene&);
			bool importSprite (tinyxml2::XMLElement* spriteNode, pGr::Scene& m_Scene);
			bool importAnimation (tinyxml2::XMLElement* Elem, std::vector<Animation>** Anim);
	};
}
#endif//IMPORTER_H