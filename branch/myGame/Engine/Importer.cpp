#define NOMINMAX
#include "Importer.h"
#include "Entity3D.h"
#include "Renderer.h"
#include "Mathjavi.h"
#include "Scene.h"
#include "Mesh.h"
#include "Node.h"

#include <limits>
#include <cstddef>
#include <iostream>
#include<sstream>

#include "../assimp/assimp/include/Importer.hpp"
#include "../assimp/assimp/include/scene.h"
#include "../assimp/assimp/include/postprocess.h"


using namespace pGr;
Importer* Importer::Instance = NULL;
Importer::Importer () {

}
Importer::~Importer() {
}

bool Importer::init(Renderer* renderer){
	m_Renderer = renderer;
	return true;
}

bool Importer::import3DScene (const std::string& rkFilename, Node& node){

	Assimp::Importer kImporter;
	const aiScene* pkAiScene = kImporter.ReadFile(rkFilename, aiProcess_Triangulate | aiProcess_SortByPType);
	importNode(pkAiScene->mRootNode, pkAiScene, node);
	return true;
}
bool Importer::importNode (const aiNode* pkAiNode, const aiScene* pkAiScene, Node& node)
{
	node.setName( pkAiNode->mName.C_Str() );

	aiVector3t<float> v3AiScaling;
	aiQuaterniont<float> qAiRotation;
	aiVector3t<float> v3AiPosition;

	pkAiNode->mTransformation.Decompose(v3AiScaling, qAiRotation, v3AiPosition);

	node.setPosition(v3AiPosition.x, v3AiPosition.y, v3AiPosition.z);
	node.setScale(v3AiScaling.x, v3AiScaling.y, v3AiScaling.z);

	float fRotX, fRotY, fRotZ;
	MATHJAVI::quaternionToEuler(qAiRotation.x, qAiRotation.y, qAiRotation.z, qAiRotation.w, fRotX, fRotY, fRotZ);
	node.setRotation(fRotX, fRotY, fRotZ);
	//Creando aabb
	float fMaxX = std::numeric_limits<float>::lowest();
	float fMaxY = std::numeric_limits<float>::lowest();
	float fMaxZ = std::numeric_limits<float>::lowest();

	float fMinX = std::numeric_limits<float>::max();
	float fMinY = std::numeric_limits<float>::max();
	float fMinZ = std::numeric_limits<float>::max();
	//------------

	//Childs nodes.
	for(unsigned int i=0; i<pkAiNode->mNumChildren; i++)
	{
		Node* pkNode = new Node();
		node.addChild(pkNode);
		pkNode->setParent(&node);
		importNode(pkAiNode->mChildren[i], pkAiScene, *pkNode);


		//Actualizo las AABB tomando en cuenta los nodos.	
		float AabbMx = pkNode->getPosX() + (pkNode->getAABB().offset()->x + (pkNode->getAABB().width() / 2));
		float AabbMy = pkNode->getPosY() + (pkNode->getAABB().offset()->y + (pkNode->getAABB().height() / 2));
		float AabbMz = pkNode->getPosZ() + (pkNode->getAABB().offset()->z + (pkNode->getAABB().depth() / 2));

		float Aabbmx = pkNode->getPosX() + (pkNode->getAABB().offset()->x - (pkNode->getAABB().width() / 2));
		float Aabbmy = pkNode->getPosY() + (pkNode->getAABB().offset()->y - (pkNode->getAABB().height() / 2));
		float Aabbmz = pkNode->getPosZ() + (pkNode->getAABB().offset()->z - (pkNode->getAABB().depth() / 2));

		if (fMaxX < AabbMx) fMaxX = AabbMx;
		if (fMaxY < AabbMy) fMaxY = AabbMy;
		if (fMaxZ < AabbMz) fMaxZ = AabbMz;

		if (fMinX > Aabbmx) fMinX = Aabbmx;
		if (fMinY > Aabbmy) fMinY = Aabbmy;
		if (fMinZ > Aabbmz) fMinZ = Aabbmz;
	}
	//----------

	//Childs Meshes.
	for(unsigned int i=0; i<pkAiNode->mNumMeshes; i++)
	{
		Mesh* pkMesh = new Mesh(this->getRenderer());
		node.addChild(pkMesh);
		pkMesh->setParent(&node);
		aiMesh* pkAiMesh = pkAiScene->mMeshes[ pkAiNode->mMeshes[i] ];
		aiMaterial* pkAiMaterial = pkAiScene->mMaterials[pkAiMesh->mMaterialIndex];
		importMesh(pkAiMesh, pkAiMaterial, *pkMesh);
		
		//Actualizo las AABB tomando en cuenta los meshes.
		float fAabbMaxX = pkMesh->getPosX() + (pkMesh->getAABB().offset()->x + (pkMesh->getAABB().width() / 2));
		float fAabbMaxY = pkMesh->getPosY() + (pkMesh->getAABB().offset()->y + (pkMesh->getAABB().height() / 2));
		float fAabbMaxZ = pkMesh->getPosZ() + (pkMesh->getAABB().offset()->z + (pkMesh->getAABB().depth() / 2));

		float fAabbMinX = pkMesh->getPosX() + (pkMesh->getAABB().offset()->x - (pkMesh->getAABB().width() / 2));
		float fAabbMinY = pkMesh->getPosY() + (pkMesh->getAABB().offset()->y - (pkMesh->getAABB().height() / 2));
		float fAabbMinZ = pkMesh->getPosZ() + (pkMesh->getAABB().offset()->z - (pkMesh->getAABB().depth() / 2));

		if (fMaxX < fAabbMaxX) fMaxX = fAabbMaxX;
		if (fMaxY < fAabbMaxY) fMaxY = fAabbMaxY;
		if (fMaxZ < fAabbMaxZ) fMaxZ = fAabbMaxZ;

		if (fMinX > fAabbMinX) fMinX = fAabbMinX;
		if (fMinY > fAabbMinY) fMinY = fAabbMinY;
		if (fMinZ > fAabbMinZ) fMinZ = fAabbMinZ;
		
	}
	node.getAABB().setDataAABB(fabs(fMaxX - fMinX), fabs(fMaxY - fMinY), fabs(fMaxZ - fMinZ), (fMinX - fMaxX) / 2 - node.getPosX(), (fMinY - fMaxY) / 2 - node.getPosY(), (fMinZ - fMaxZ) / 2 - node.getPosZ());
	cout << " minx: " << fMinX << " maxx: " << fMaxX << " miny: " << fMinY << " maxy: " << fMaxY << " minz: " << fMinZ << " maxz: " << fMaxZ << endl;
	return true;
}
bool Importer::importMesh(const aiMesh* pkAiMesh, const aiMaterial* pkAiMaterial, Mesh& mesh)
{
	mesh.setName( pkAiMesh->mName.C_Str() );

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
			pakVertices[i].v = -pkAiMesh->mTextureCoords[0][i].y;
		}

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
	mesh.setDataMesh(pakVertices, pkAiMesh->mNumVertices, pGr::Primitive::TriangleList, pausIndices, uiIndexCount);
	mesh.setName(pkAiMesh->mName.C_Str());

	if(pkAiMaterial){
		aiString kAiTexturePath;
		pkAiMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &kAiTexturePath);

		std::string kTexturePath( kAiTexturePath.C_Str());

		if( !kTexturePath.empty() && kTexturePath.at(0) == '/' )
		{
			kTexturePath = "." + kTexturePath;
		}
		
		std::stringstream ss;
		std::string s( ss.str() );
		OutputDebugString( s.c_str() );

		Texture TheTexture = m_Renderer->loadTexture("assets/"+kTexturePath);
		mesh.setTexture(TheTexture);
	}
	
	delete[] pakVertices;
	pakVertices = NULL;

	return true;
}

Importer* Importer::getInstance()
{
	if(Instance == NULL){
		Instance = new Importer();
	}

	return Instance;
}

