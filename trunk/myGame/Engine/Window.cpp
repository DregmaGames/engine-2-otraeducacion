//-----------------------------------------------
#include "Window.h"
//-----------------------------------------------
using namespace pGr;

Window::Window(HINSTANCE hInstance)
	:
	m_hWnd(NULL),
	m_hInstance(hInstance){}

Window::~Window(){
	if(m_hWnd) DestroyWindow(m_hWnd);
}
bool Window::setWindowName(std::string p){
	SetWindowText(m_hWnd,p.c_str());
	return true;
}
//----------------------------------
bool Window::createWindow(unsigned int uiWidth,unsigned int uiHeight)
{   //reg window

	WNDCLASS kWC={0}; // estructura de la clase ventana
	memset(static_cast<void *> (&kWC), 0, sizeof(WNDCLASS));
	kWC.style = CS_HREDRAW | CS_VREDRAW;
	kWC.lpfnWndProc =  WindProc; //Procedimiento para el manejo de mensajes
	kWC.hInstance = m_hInstance; //instancia de la aplicacion
	kWC.hbrBackground = (HBRUSH) COLOR_BTNFACE; //FONDO
	kWC.lpszClassName = "Engine"; // Nombre de la clase ventana

	//Se registra la clase ventana y se la verifica
	if (!RegisterClass(&kWC))
		return false;

	m_hWnd = CreateWindow("Engine", //Nombre de la clase ventana
						  windowName.c_str(), //Titulo de la ventana
						  WS_VISIBLE | WS_OVERLAPPEDWINDOW , //Coloca la ventana hasta arriba
						  CW_USEDEFAULT, //posicion de la ventana
						  CW_USEDEFAULT, //Tamaño de la ventana
						  uiWidth +8 ,  
						  uiHeight + 30,  
						  NULL, 
						  NULL , 
						  m_hInstance, //la instancia
						  NULL);
	//verificamos que la ventana se creara correctamente
	if (m_hWnd != NULL) return true;
		return false;
}
//prototipo del Procedimiento de windows
LRESULT CALLBACK Window::WindProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{	
	switch(message)
	{	
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	//return DefWindowProc(hWnd, message, wParam, lParam);
	return 0;
}
//-----------------------------------------------