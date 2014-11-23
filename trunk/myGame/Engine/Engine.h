#ifndef MYENGINE_H
#define MYENGINE_H

#include "myEngine_API.h"
#include "pg1_input.h"
#include "pg1_directinput.h"
#include "pg1_timer.h"
#include "Physics.h"
//-------------------------------
namespace pGr
{
	class Renderer;
	class Window;
	class Timer;
	class Game;
	class Importer;
	class Physics;
	//------------------------------------------
	class MYENGINE_API Engine{
	public:
		Engine(HINSTANCE hInstance,unsigned int uiWidth,unsigned int uiHeight);
		~Engine();
		bool init ();
		void run();
		Game* pgGame;
		
		//rendering
	private:
		Importer* m_pkImport;
		HINSTANCE m_hInstance;
		unsigned int m_uiWidth;
		unsigned int m_uiHeight;
		Window* m_pkWindow;
		Renderer* m_pkRenderer;
		DirectInput* m_pkInput;		
		Timer* m_pkTimer;
		Physics* m_pkPhysics;
	};
	//-----------------------------------------------
}
#endif