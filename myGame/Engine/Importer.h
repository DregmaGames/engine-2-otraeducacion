#ifndef IMPORTER_H
#define IMPORTER_H

#include <map>
#include <list>
#include <vector>
#include <string>

#include "myEngine_API.h"
#include "tinyxml2.h"
#include "RenderTypes.h"

// Assimp
struct aiNode;
struct aiMesh;
struct aiMaterial;
struct aiScene;
#pragma comment(lib, "../assimp/assimp/lib/assimp.lib")

namespace pGr{

	class Mesh;
	class Node;
	class Scene;
	class Renderer;
	class MYENGINE_API Importer
	{
		friend class Engine;

		public:

			bool init(Renderer*);
			static Importer* getInstance();
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
	};
}
#endif//IMPORTER_H