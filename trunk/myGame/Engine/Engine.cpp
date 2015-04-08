#include "Engine.h"
//-----------------------------------------------
#include "Window.h"
#include "Renderer.h"
#include "pg1_timer.h"
#include "Scene.h"
#include "Mesh.h"
//-----------------------------------------------
#include "Game.h"
#include "Importer.h"
//-----------------------------------------------
#include <sstream>
//-----------------------------------------------
using namespace pGr;
Engine::Engine(HINSTANCE hInstance, unsigned int uiWidth, unsigned int uiHeight)
	:
	m_hInstance(hInstance),
	m_uiWidth(uiWidth),
	m_uiHeight(uiHeight),
	m_pkWindow(new Window(hInstance)),
	m_rkRenderer(new Renderer()),
	pgGame(NULL),
	m_pkInput(new DirectInput()),
	m_pkTimer(new Timer())
{
	//Nothing to do
}

Engine::~Engine()
{
	delete m_pkTimer;
	m_pkTimer = NULL;
	delete m_pkInput;
	m_pkInput = NULL;
	delete m_rkRenderer;
	m_rkRenderer = NULL;
	delete m_pkWindow;
	m_pkWindow = NULL;
}
bool Engine::init(){
	//create window
	if (m_pkWindow->createWindow(m_uiWidth, m_uiHeight) == TRUE && m_rkRenderer->init(m_pkWindow->getHWND()) == TRUE &&
		m_pkInput->init(m_hInstance, m_pkWindow->getHWND()))return true;
	return false;
}
void Engine::run()
{
	//frame loop
	bool bDone = false;
	MSG kMsg;
	if (!pgGame){
		return;
	}
	if (!pgGame->init(*m_rkRenderer)){
		return;
	}

	m_pkTimer->firstMeasure();

	while (!bDone)
	{
		Mesh::amountDraw = 0;

		m_pkTimer->measure();

		m_pkInput->reacquire();
		//render frame
		//m_pkPhysics->update(m_pkTimer->timeBetweenFrames());

		m_rkRenderer->beginFrame();
		pgGame->frame(*m_rkRenderer, *m_pkInput, *m_pkTimer);
		//pgGame->getCurrentScene()->frame(*m_rkRenderer,*m_pkImport,*pgGame,*m_pkInput);
		//pgGame->getCurrentScene()->drawScene(m_rkRenderer,m_pkTimer);
		m_rkRenderer->endFrame();

		static std::stringstream Title;
		Title.str("");
		Title << m_pkWindow->getWindowName() << " (" << m_pkTimer->fps() << " FPS) Scene: " << "Amount MEsh: " << Mesh::amountDraw << " || Enchine <Frere> <Rios <Bianco> <Mercatante>";
		m_pkWindow->setWindowName(Title.str());

		// capturo el mensaje de Windows---------
		if (PeekMessage(&kMsg, NULL, 0, 0, PM_REMOVE))
		{
			// Pasamos el mensaje de vuelta a Windows
			TranslateMessage(&kMsg);
			DispatchMessage(&kMsg);
		}
		//---------------------------------------

		if (kMsg.message == WM_QUIT)
			bDone = true;
	}
	pgGame->deinit();
}

void Engine::setGame(Game* game)
{
	pgGame = game;
}
//-----------------------------------------------
