#include "MyEngine.h"
//-----------------------------------------------
#include "Window.h"
#include "Renderer.h"
#include "pg1_timer.h"
#include "Scene.h"
//-----------------------------------------------
#include "Game.h"
#include "Importer.h"
//-----------------------------------------------
#include <sstream>
//-----------------------------------------------
using namespace pGr;
// Declaraciones.
Engine::Engine(HINSTANCE hInstance,unsigned int uiWidth,unsigned int uiHeight)
	:
	m_hInstance(hInstance),
	m_uiWidth(uiWidth),
	m_uiHeight(uiHeight),
	m_pkWindow(new Window(hInstance)),
	m_pkRenderer(new Renderer()),
	pgGame(NULL),
	m_pkInput( new DirectInput()),
	m_pkTimer(new Timer()),
	m_pkImport(new Importer())
	{
		//Nothing to do
	}

Engine::~Engine(){
	delete m_pkTimer;
	m_pkTimer = NULL;
	delete m_pkInput;
	m_pkInput = NULL;
	delete m_pkImport;
	m_pkImport = NULL;
	delete m_pkRenderer;
	m_pkRenderer = NULL;
	delete m_pkWindow;
	m_pkWindow = NULL;
}
bool Engine::init (){
	//create window
	if(m_pkWindow->createWindow(m_uiWidth,m_uiHeight) == TRUE 
		&& 
		m_pkRenderer->init(m_pkWindow->getHWND()) == TRUE 
		&&
		m_pkInput->init(m_hInstance,m_pkWindow->getHWND())
		&&
		m_pkImport->init(m_pkRenderer) == TRUE)
		return true;
	return false;
}
void Engine::run(){
	//frame loop
	bool bDone= false;
	MSG kMsg;
	if(!pgGame){
		return;
	}
	if(!pgGame->init(*m_pkRenderer,*m_pkImport)){
		return;
	}
	if( !pgGame->getCurrentScene()->init(*m_pkImport) ){
		return;
	}
	m_pkTimer->firstMeasure();
	while(!bDone){
		m_pkTimer->measure();
		
		//Update FPS
		static std::stringstream Title;
		Title.str("");
		Title << m_pkWindow->getWindowName() << " (" << m_pkTimer->fps() << " FPS) Scene: " << pgGame->getCurrentScene()->m_pkName << " || Enchine <Frere> <Rios <Bianco> <Mercatante>";
		m_pkWindow->setWindowName(Title.str());
		//---------------------------------------

		m_pkInput->reacquire();
		//render frame
		m_pkRenderer->beginFrame();
		pgGame->frame(*m_pkRenderer,*m_pkInput, *m_pkTimer,*m_pkImport);
		pgGame->getCurrentScene()->frame(*m_pkRenderer,*m_pkImport,*pgGame,*m_pkInput);
		pgGame->getCurrentScene()->drawScene(m_pkRenderer,m_pkTimer);
		m_pkRenderer->endFrame();

		// capturo el mensaje de Windows
		if(PeekMessage(&kMsg,NULL,0,0,PM_REMOVE))
		{
		// Pasamos el mensaje de vuelta a Windows
			TranslateMessage(&kMsg);
			DispatchMessage(&kMsg);
		}

		if(kMsg.message == WM_QUIT)
			bDone = true;
	}
	pgGame->getCurrentScene()->deInit();
	pgGame->deinit();
}
//-----------------------------------------------