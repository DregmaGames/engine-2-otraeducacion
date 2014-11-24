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
	class Game;
	class Timer;
	class Input;
	class Window;
	class Physics;
	class Renderer;
	class Importer;
	//------------------------------------------
	class MYENGINE_API Engine
	{

	public:
		Engine(HINSTANCE hInstance,unsigned int uiWidth,unsigned int uiHeight);
		~Engine();

		bool init ();
		void run();

		Window* m_pkWindow;
		Renderer* m_pkRenderer;

		void setGame(Game* game);
		
	//rendering
	private:

		Game* pgGame;
		Timer* m_pkTimer;
		Physics* m_pkPhysics;
		HINSTANCE m_hInstance;
		DirectInput* m_pkInput;
		unsigned int m_uiWidth;
		unsigned int m_uiHeight;			
	};
	//-----------------------------------------------
}
#endif