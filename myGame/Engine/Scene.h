#ifndef SCENE_H
#define SCENE_H

#include "Entity2D.h"
#include "Animation.h"
#include "Importer.h"
#include "MyEngine.h"
#include <list>
namespace pGr{
	class MYENGINE_API Scene{
	public:
		char* xmlPath;
		Entity2D GetObjByName(char* Name);
	public:
		List<pGr::Entity2D> Objects;
	}
};
#endif