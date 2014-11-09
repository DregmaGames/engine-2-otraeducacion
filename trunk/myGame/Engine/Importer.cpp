#define NOMINMAX
#include "Importer.h"
#include "Scene.h"
#include "Animation.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Node.h"
#include "Entity3D.h"
#include "../assimp/assimp/include/Importer.hpp"
#include "../assimp/assimp/include/scene.h"
#include "../assimp/assimp/include/postprocess.h"
#include <limits>
#include <cstddef>
#include <iostream>
#include<sstream>
#include<string>

using namespace pGr;
Importer* Importer::Instance = NULL;
Importer::Importer () 
{

}
Importer::~Importer()
{

}

bool Importer::init(Renderer* renderer)
{
	m_Renderer = renderer;
	return true;
}

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
		float fAabbMaxX = pkNode->getPosX() + ( pkNode->aabb().offset()->x + ( pkNode->aabb().width() / 2 ) );
		float fAabbMaxY = pkNode->getPosY() + ( pkNode->aabb().offset()->y + ( pkNode->aabb().height() / 2 ) );
		float fAabbMaxZ = pkNode->getPosZ() + ( pkNode->aabb().offset()->z + ( pkNode->aabb().depth() / 2 ) );

		float fAabbMinX = pkNode->getPosX() + ( pkNode->aabb().offset()->x - ( pkNode->aabb().width() / 2 ) );
		float fAabbMinY = pkNode->getPosY() + ( pkNode->aabb().offset()->y - ( pkNode->aabb().height() / 2 ) );
		float fAabbMinZ = pkNode->getPosZ() + ( pkNode->aabb().offset()->z - ( pkNode->aabb().depth() / 2 ) );

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
		float fAabbMaxX = pkMesh->getPosX() + ( pkMesh->aabb().offset()->x + ( pkMesh->aabb().width() / 2 ) );
		float fAabbMaxY = pkMesh->getPosY() + ( pkMesh->aabb().offset()->y + ( pkMesh->aabb().height() / 2 ) );
		float fAabbMaxZ = pkMesh->getPosZ() + ( pkMesh->aabb().offset()->z + ( pkMesh->aabb().depth() / 2 ) );

		float fAabbMinX = pkMesh->getPosX() + ( pkMesh->aabb().offset()->x - ( pkMesh->aabb().width() / 2 ) );
		float fAabbMinY = pkMesh->getPosY() + ( pkMesh->aabb().offset()->y - ( pkMesh->aabb().height() / 2 ) );
		float fAabbMinZ = pkMesh->getPosZ() + ( pkMesh->aabb().offset()->z - ( pkMesh->aabb().depth() / 2 ) );

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
								
								(fMinX + fMaxX) / 2 - node.getPosX(), 
								(fMinY + fMaxY) / 2 - node.getPosY(), 
								(fMinZ + fMaxZ) / 2 - node.getPosZ());
	
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

		std::string kTexturePath( kAiTexturePath.C_Str());

		// append '.' if texture is inside folder
		if( !kTexturePath.empty() && kTexturePath.at(0) == '/' )
		{
			kTexturePath = "." + kTexturePath;
		}
		std::stringstream ss;
		ss << "CARA DE CHOTA: "<<kAiTexturePath.C_Str()<< std::endl;
		std::string s( ss.str() );
		OutputDebugString( s.c_str() );

		Texture TheTexture = m_Renderer->loadTexture("assets/"+kTexturePath);
		//Texture TheTexture = m_Renderer->loadTexture("assets/TextureMap.png");
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