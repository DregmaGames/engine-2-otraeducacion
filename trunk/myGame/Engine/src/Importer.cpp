#include "Importer.h"
#include "Sprite.h"
#include "Quad.h"
#include "Animation.h"
using namespace pGr;
Importer::Importer () {
}
Importer::~Importer(){
}
bool Importer::importScene(std::string xmlPath,pGr::Scene& m_Scene){
	tinyxml2::XMLDocument xml;
	xml.LoadFile(xmlPath.c_str());
	if(xml.Error())return false;
	tinyxml2::XMLElement *root = xml.FirstChildElement("SCENE");
	importQuad(root, m_Scene);
	importSprite(root, m_Scene);
	return true;
}
bool Importer::importQuad (tinyxml2::XMLElement* quadNode, pGr::Scene& m_Scene){
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
bool Importer::importSprite(tinyxml2::XMLElement* spriteNode, pGr::Scene& m_Scene){
	tinyxml2::XMLElement* Obj=spriteNode->FirstChildElement("SPRITE");
	tinyxml2::XMLElement* Obj1=spriteNode->FirstChildElement("INSTANCE");
	while(Obj!=NULL){
		std::string name= Obj->Attribute("name");
		std::string pathTexture = Obj->Attribute("texture");
		int r = Obj->IntAttribute("r");
		int g = Obj->IntAttribute("g");
		int b = Obj->IntAttribute("b");
		pGr::Texture textureAux = m_Renderer->loadTexture(pathTexture,PG1_COLOR_RGB(r,g,b));
		std::vector<Animation>* listaAnim = new std::vector<Animation>();
		importAnimation(Obj->FirstChildElement("ANIMATION"),&listaAnim);
		Obj1 = spriteNode->FirstChildElement("INSTANCE");

		while(Obj1!=NULL){
			pGr::Sprite* mkSprite = new pGr::Sprite();
			if(Obj1->Attribute("sprite") == name){
				mkSprite->setName(name);
				mkSprite->setPos(Obj1->FloatAttribute("posX"),Obj1->FloatAttribute("posY"), Obj1->FloatAttribute("posZ"));
				mkSprite->setRotation(Obj1->FloatAttribute("rotation"));
				mkSprite->setScale(Obj1->FloatAttribute("scaleX"),Obj1->FloatAttribute("scaleY"));
				mkSprite->setTexture(textureAux);
			}
			mkSprite->addAnimation(*listaAnim);
			m_Scene.m_kObjects.push_back(mkSprite);
			Obj1=Obj1->NextSiblingElement("INSTANCE");
		}
		Obj = Obj->NextSiblingElement("SPRITE");
	}
	return true;
}
bool Importer::importAnimation (tinyxml2::XMLElement* Elem, std::vector<Animation>** Anim){
	while(Elem != NULL){
		Animation* skAnim= new Animation();
		std::string name = Elem->Attribute("name");
		int lenght= Elem->IntAttribute("lenght");
		int width= Elem->IntAttribute("width");
		int height=Elem->IntAttribute("height");
		skAnim->setName(name);
		skAnim->setLength(lenght);
		tinyxml2::XMLElement* FrameObj = Elem->FirstChildElement("FRAME");
		while(FrameObj != NULL){
			skAnim->addFrame(width,height, FrameObj->FloatAttribute("posX"),FrameObj->FloatAttribute("posY"),FrameObj->FloatAttribute("width"),FrameObj->FloatAttribute("height"));
			FrameObj= FrameObj->NextSiblingElement("FRAME");
		}
		(*Anim)->push_back(*skAnim);
		Elem = Elem->NextSiblingElement("ANIMATION");
	}
	return true;
}
bool Importer::init(Renderer* a){
	m_Renderer = a;
	return true;
}