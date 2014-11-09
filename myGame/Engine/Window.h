#ifndef WINDOWS_H
#define WINDOWS_H
//------------------------------------------------------------------------
#include <Windows.h>
#include <string>
//------------------------------------------------------------------------
namespace pGr
{
	class Window
	{
	public:	
		Window(HINSTANCE hInstance);
		~Window();

		std::string getWindowName(){return windowName;}
		bool setWindowName(std::string p);
		bool createWindow(unsigned int uiWidth,unsigned int uiHeight);
		HWND getHWND(){ return m_hWnd; }
		static LRESULT CALLBACK WindProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	private:
		HWND m_hWnd;
		HINSTANCE m_hInstance;
		std::string windowName;
	};

}
#endif //WINDOW_H