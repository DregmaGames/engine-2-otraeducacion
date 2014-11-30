#ifndef GAME_H
#define GAME_H

#include "myEngine_API.h"
#include <iostream>
#include <string>
#include <vector>
//---------------------------------------
namespace pGr
{
	class Timer;
	class Physics;
	class Renderer;
	class DirectInput;
	class Scene;
	class Importer;
	
	class MYENGINE_API Game
	{
	public:
		Game();

		bool getDone();
		void setDone(bool done);
		virtual bool init (pGr::Renderer&, pGr::Physics& physics)=0;
		virtual void frame(pGr::Renderer&,pGr::DirectInput& rkInput, pGr::Timer& t)=0;
		virtual void deinit()=0;
	
	private:
		
		std::vector<Scene*> scenesList;
		bool done;
	};
}
#endif