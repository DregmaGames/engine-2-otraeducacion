#define NOMINMAX
#include "Importer.h"
#include "Scene.h"
#include "Sprite.h"
#include "Quad.h"
#include "Animation.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Node.h"
#include "Scene.h"
#include "Sprite.h"
#include "Entity3D.h"
#include "Entity2D.h"
#include "../assimp/assimp/include/Importer.hpp"
#include "../assimp/assimp/include/scene.h"
#include "../assimp/assimp/include/postprocess.h"
#include <limits>
#include <cstddef>
#include <iostream>


using namespace pGr;
Importer* Importer::Instance = NULL;
Importer::Importer () 
{
}
Importer::~Importer()
{
}
//--------------------------OLD 2D IMPORTER -----------------------------//
bool Importer::importScene(std::string xmlPath,pGr::Scene& m_Scene)
{

	tinyxml2::XMLDocument xml;
	xml.LoadFile(xmlPath.c_str());
	if(xml.Error())return false;
	tinyxml2::XMLElement *root = xml.FirstChildElement("SCENE");
	importQuad(root, m_Scene);
	importSprite(root, m_Scene);
	return true;
}
bool Importer::importQuad (tinyxml2::XMLElement* quadNode, pGr::Scene& m_Scene)
{
	tinyxml2::XMLElement* Obj=quadNode->FirstChildElement("QUAD");
	while(Obj!=NULL){
		Quad* Aux=new Quad();
		Aux->setName(Obj->Attribute("name"));
		Aux->setPos(Obj->FloatAttribute("posX"),Obj->FloatAttribute("posY"), Obj->FloatAttribute("posZ"));
		Aux->setScale(Obj->FloatAttribute("scaleX"),Obj->FloatAttribute("scaleY"));
		Aux->setRotation(Obj->FloatAttribute("rotation"));
		Aux->setColor(PG1_COLOR_RGB(Obj->IntAttribute("r"),Obj->IntAttribute("g"),Obj->IntAttribute("b")));
		m_Scene.m_kObjects.push_back(Aux);
		Obj=Obj->NextSiblingElement("QUAD");
	}
	return true;
}
bool Importer::importSprite(tinyxml2::XMLElement* spriteNode, pGr::Scene& m_Scene)
{
	tinyxml2::XMLElement* Obj=spriteNode->FirstChildElement("SPRITE");
	tinyxml2::XMLElement* Obj1=spriteNode->FirstChildElement("INSTANCE");
	while(Obj!=NULL)
	{
		std::string name= Obj->Attribute("name");
		std::string pathTexture = Obj->Attribute("texture");
		int r = Obj->IntAttribute("r");
		int g = Obj->IntAttribute("g");
		int b = Obj->IntAttribute("b");
		//pGr::Texture textureAux = m_Renderer->loadTexture(pathTexture,PG1_COLOR_RGB(r,g,b));
		std::vector<Animation>* listaAnim = new std::vector<Animation>();
		importAnimation(Obj->FirstChildElement("ANIMATION"),&listaAnim);
		Obj1 = spriteNode->FirstChildElement("INSTANCE");

		while(Obj1!=NULL)
		{
			pGr::Sprite* mkSprite = new pGr::Sprite();
			if(Obj1->Attribute("sprite") == name){
				mkSprite->setName(name);
				mkSprite->setPos(Obj1->FloatAttribute("posX"),Obj1->FloatAttribute("posY"), Obj1->FloatAttribute("posZ"));
				mkSprite->setRotation(Obj1->FloatAttribute("rotation"));
				mkSprite->setScale(Obj1->FloatAttribute("scaleX"),Obj1->FloatAttribute("scaleY"));
				//mkSprite->setTexture(textureAux);
			}
			mkSprite->addAnimation(*listaAnim);
			m_Scene.m_kObjects.push_back(mkSprite);
			Obj1=Obj1->NextSiblingElement("INSTANCE");
		}
		Obj = Obj->NextSiblingElement("SPRITE");
	}
	return true;
}
bool Importer::importAnimation (tinyxml2::XMLElement* Elem, std::vector<Animation>** Anim)
{
	while(Elem != NULL)
	{
		Animation* skAnim= new Animation();
		std::string name = Elem->Attribute("name");
		int lenght= Elem->IntAttribute("lenght");
		int width= Elem->IntAttribute("width");
		int height=Elem->IntAttribute("height");
		skAnim->setName(name);
		skAnim->setLength(lenght);
		tinyxml2::XMLElement* FrameObj = Elem->FirstChildElement("FRAME");
		while(FrameObj != NULL)
		{
			skAnim->addFrame(width,height, FrameObj->FloatAttribute("posX"),FrameObj->FloatAttribute("posY"),FrameObj->FloatAttribute("width"),FrameObj->FloatAttribute("height"));
			FrameObj= FrameObj->NextSiblingElement("FRAME");
		}
		(*Anim)->push_back(*skAnim);
		Elem = Elem->NextSiblingElement("ANIMATION");
	}
	return true;
}
bool Importer::init(Renderer* a)
{
	m_Renderer = a;
	return true;
}
// ---------------------------------------------------------------------//
bool Importer::import3DScene (const std::string& rkFilename, Node& node)
{

	Assimp::Importer kImporter;
	const aiScene* pkAiScene = kImporter.ReadFile(rkFilename, aiProcess_Triangulate | aiProcess_SortByPType);
	importNode(pkAiScene->mRootNode, pkAiScene, node);
	
	return true;
}

bool Importer::importNode (const aiNode* pkAiNode, const aiScene* pkAiScene, Node& node)
{
	// import transformation
	aiVector3t<float> v3AiScaling;
	aiQuaterniont<float> qAiRotation;
	aiVector3t<float> v3AiPosition;

	pkAiNode->mTransformation.Decompose(v3AiScaling, qAiRotation, v3AiPosition);

	node.setPos(v3AiPosition.x, v3AiPosition.y, v3AiPosition.z); // Seteo POS
	node.setScale(v3AiScaling.x, v3AiScaling.y, v3AiScaling.z); // Seteo Scale
	float fRotX, fRotY, fRotZ;
	quaternionToEulerAngles(qAiRotation.x, qAiRotation.y, qAiRotation.z, qAiRotation.w, fRotX, fRotY, fRotZ); // Uso QuaternionToEuler :)
	
	node.setRotation(fRotX, fRotY, fRotZ); // Seteo Rotation

	//INTENTO crear AABB.
	float fMaxX = std::numeric_limits<float>::lowest();
	float fMaxY = std::numeric_limits<float>::lowest();
	float fMaxZ = std::numeric_limits<float>::lowest();

	float fMinX = std::numeric_limits<float>::max();
	float fMinY = std::numeric_limits<float>::max();
	float fMinZ = std::numeric_limits<float>::max();
	

	// Importo Child Nodes

	for(unsigned int i=0; i<pkAiNode->mNumChildren; i++)
	{
		Node* pkNode = new Node();
		node.addChild(pkNode);

		pkNode->setParent(&node);

		importNode(pkAiNode->mChildren[i], pkAiScene, *pkNode);

		//Ajusto AABB ?
		float fAabbMaxX = pkNode->posX() + ( pkNode->aabb().offset()->x + ( pkNode->aabb().width() / 2 ) );
		float fAabbMaxY = pkNode->posY() + ( pkNode->aabb().offset()->y + ( pkNode->aabb().height() / 2 ) );
		float fAabbMaxZ = pkNode->posZ() + ( pkNode->aabb().offset()->z + ( pkNode->aabb().depth() / 2 ) );

		float fAabbMinX = pkNode->posX() + ( pkNode->aabb().offset()->x - ( pkNode->aabb().width() / 2 ) );
		float fAabbMinY = pkNode->posY() + ( pkNode->aabb().offset()->y - ( pkNode->aabb().height() / 2 ) );
		float fAabbMinZ = pkNode->posZ() + ( pkNode->aabb().offset()->z - ( pkNode->aabb().depth() / 2 ) );

		if(fMaxX < fAabbMaxX) fMaxX = fAabbMaxX;
		if(fMaxY < fAabbMaxY) fMaxY = fAabbMaxY;
		if(fMaxZ < fAabbMaxZ) fMaxZ = fAabbMaxZ;

		if(fMinX > fAabbMinX) fMinX = fAabbMinX;
		if(fMinY > fAabbMinY) fMinY = fAabbMinY;
		if(fMinZ > fAabbMinZ) fMinZ = fAabbMinZ;

		
	}

	// Importo Child Meshes

	for(unsigned int i=0; i<pkAiNode->mNumMeshes; i++)
	{
		Mesh* pkMesh = new Mesh(this->getRenderer());
		node.addChild(pkMesh);

		pkMesh->setParent(&node);

		aiMesh* pkAiMesh = pkAiScene->mMeshes[ pkAiNode->mMeshes[i] ];
		aiMaterial* pkAiMaterial = pkAiScene->mMaterials[pkAiMesh->mMaterialIndex];
		importMesh(pkAiMesh, pkAiMaterial, *pkMesh);

		//	Actualizo nuevamente los AABB (Pero para meshes!)
		float fAabbMaxX = pkMesh->posX() + ( pkMesh->aabb().offset()->x + ( pkMesh->aabb().width() / 2 ) );
		float fAabbMaxY = pkMesh->posY() + ( pkMesh->aabb().offset()->y + ( pkMesh->aabb().height() / 2 ) );
		float fAabbMaxZ = pkMesh->posZ() + ( pkMesh->aabb().offset()->z + ( pkMesh->aabb().depth() / 2 ) );

		float fAabbMinX = pkMesh->posX() + ( pkMesh->aabb().offset()->x - ( pkMesh->aabb().width() / 2 ) );
		float fAabbMinY = pkMesh->posY() + ( pkMesh->aabb().offset()->y - ( pkMesh->aabb().height() / 2 ) );
		float fAabbMinZ = pkMesh->posZ() + ( pkMesh->aabb().offset()->z - ( pkMesh->aabb().depth() / 2 ) );

		if(fMaxX < fAabbMaxX) fMaxX = fAabbMaxX;
		if(fMaxY < fAabbMaxY) fMaxY = fAabbMaxY;
		if(fMaxZ < fAabbMaxZ) fMaxZ = fAabbMaxZ;

		if(fMinX > fAabbMinX) fMinX = fAabbMinX;
		if(fMinY > fAabbMinY) fMinY = fAabbMinY;
		if(fMinZ > fAabbMinZ) fMinZ = fAabbMinZ;
		
	}

		node.aabb().setData( fabs(fMaxX - fMinX), 
								fabs(fMaxY - fMinY), 
								fabs(fMaxZ - fMinZ), 
								
								(fMinX + fMaxX) / 2 - node.posX(), 
								(fMinY + fMaxY) / 2 - node.posY(), 
								(fMinZ + fMaxZ) / 2 - node.posZ());
	


	return true;
}
bool Importer::importMesh(const aiMesh* pkAiMesh, const aiMaterial* pkAiMaterial, Mesh& orkMesh)
{
	
			
	float fMaxX = std::numeric_limits<float>::lowest();
	float fMaxY = std::numeric_limits<float>::lowest();
	float fMaxZ = std::numeric_limits<float>::lowest();

	float fMinX = std::numeric_limits<float>::max();
	float fMinY = std::numeric_limits<float>::max();
	float fMinZ = std::numeric_limits<float>::max();
	
	MeshVertex* pakVertices = new MeshVertex[pkAiMesh->mNumVertices];

	for(unsigned int i=0; i<pkAiMesh->mNumVertices; i++)
	{
		pakVertices[i].x = pkAiMesh->mVertices[i].x;
		pakVertices[i].y = pkAiMesh->mVertices[i].y;
		pakVertices[i].z = pkAiMesh->mVertices[i].z;
		if( pkAiMesh->mTextureCoords[0] != NULL )
		{
			pakVertices[i].u = pkAiMesh->mTextureCoords[0][i].x;
			pakVertices[i].v = pkAiMesh->mTextureCoords[0][i].y;
		}

		
		// Actualizo AABB
			if( fMaxX < pakVertices[i].x ) fMaxX = pakVertices[i].x;
			if( fMaxY < pakVertices[i].y ) fMaxY = pakVertices[i].y;
			if( fMaxZ < pakVertices[i].z ) fMaxZ = pakVertices[i].z;

			if( fMinX > pakVertices[i].x ) fMinX = pakVertices[i].x;
			if( fMinY > pakVertices[i].y ) fMinY = pakVertices[i].y;
			if( fMinZ > pakVertices[i].z ) fMinZ = pakVertices[i].z;

		
		if(pkAiMesh->HasNormals())
		{
			pakVertices[i].nx = pkAiMesh->mNormals[i].x;
			pakVertices[i].ny = pkAiMesh->mNormals[i].y;
			pakVertices[i].nz = pkAiMesh->mNormals[i].z;
		}
	}

	size_t uiIndexCount = pkAiMesh->mNumFaces * 3;
	unsigned short* pausIndices = new unsigned short[uiIndexCount];
	for(unsigned int i=0; i<pkAiMesh->mNumFaces; i++)
	{
		assert(pkAiMesh->mFaces[i].mNumIndices == 3);
		pausIndices[i * 3 + 0] = pkAiMesh->mFaces[i].mIndices[0];
		pausIndices[i * 3 + 1] = pkAiMesh->mFaces[i].mIndices[1];
		pausIndices[i * 3 + 2] = pkAiMesh->mFaces[i].mIndices[2];
	}
	orkMesh.setData(pakVertices, pkAiMesh->mNumVertices, pGr::Primitive::TriangleList, pausIndices, uiIndexCount);
	orkMesh.setName(pkAiMesh->mName.C_Str());

	if(pkAiMaterial){
		// diffuse texture
		aiString kAiTexturePath;
		pkAiMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &kAiTexturePath);

		std::string kTexturePath( kAiTexturePath.C_Str() );

		// append '.' if texture is inside folder
		if( !kTexturePath.empty() && kTexturePath.at(0) == '/' )
		{
			kTexturePath = "." + kTexturePath;
		}
		Texture TheTexture = m_Renderer->loadTexture(kTexturePath);
		orkMesh.setTexture(TheTexture);
	}
	
	delete[] pakVertices;
	pakVertices = NULL;

		//Cargo Termino de Actualizar los AABB Seteando Data...

		orkMesh.aabb().setData( fabs(fMaxX - fMinX), fabs(fMaxY - fMinY), fabs(fMaxZ - fMinZ),(fMinX + fMaxX) / 2, (fMinY + fMaxY) / 2, (fMinZ + fMaxZ) / 2);
	
	
	return true;
}
void Importer::quaternionToEulerAngles (float qX, float qY, float qZ, float qW, float& orfRotX, float& orfRotY, float& orfRotZ)
{
	double test = qX * qY + qZ * qW;
	if(test > 0.499f){
		// singularity at north pole
		orfRotX = 2.0f * atan2(qX, qW);
		orfRotY = AI_MATH_PI_F / 2.0f;
		orfRotZ = 0.0f;
		return;
	}

	if (test < -0.499f){
		// singularity at south pole
		orfRotX = -2.0f * atan2(qX, qW);
		orfRotY = - AI_MATH_PI_F / 2.0f;
		orfRotZ = 0.0f;
		return;
	}

    float sqx = qX * qX;
    float sqy = qY * qY;
    float sqz = qZ * qZ;
    
	orfRotX = atan2(2.0f * qY * qW - 2.0f * qX * qZ, 
					1.0f - 2.0f * sqy - 2.0f * sqz);
	
	orfRotY = static_cast<float>( asin(2.0f * test) );

	orfRotZ = atan2(2.0f * qX * qW - 2.0f * qY * qZ, 
					1.0f - 2.0f * sqx - 2.0f * sqz);
}
Importer* Importer::getInstance()
{
	if(Instance == NULL){
		Instance = new Importer();
	}

	return Instance;
}