#include "Importer.h"
#include "tinyxml2.h"
#include "Entity2D.h"
using namespace pGr;

Importer::Importer () {
}
Importer::~Importer(){
}
bool Importer::importScene(char* xmlPath){
	tinyxml2::XMLDocument xml;
    xml.LoadFile("assets/Test.xml");
}