#ifndef IMPORTER_H
#define IMPORTER_H
#include "Entity2D.h"
#include "tinyxml2.h"
#include "Scene.h"

//Singleton Class
class MYENGINE_API Importer
{
public:
   Importer() {}
   ~Importer(){}
   bool importScene(char* xmlPath);

   Scene scene;
private:
   bool importSprite (XMLNode& spriteNode);
   bool importTexture (XMLNode& textureNode);
   bool importAnimation (XMLNode& animationNode);
};

#endif//IMPORTER_H