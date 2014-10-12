#include "CVS_Window.h"
#include "Canvas.h"

extern CANVAS_STATEMACHINE CV_GLOBALSTATEMACHINE;

Cvs_WindowManager::Cvs_WindowManager(){
}

CVS_Window* Cvs_WindowManager::CreateNewWindow(std::string name, int x, int y, int w, int h)
{
	//Store a new window instance
	windows[name] = CVS_Window();
	CVS_Window* window = &windows[name];
	(*window).manager = this;
	(*window).windowHandler = SDL_CreateWindow(name.c_str(),x,y,w,h, SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN|SDL_WINDOW_BORDERLESS);
	//Set Window parameters.
	(*window).h = h;
	(*window).w = w;
	(*window).x = x;
	(*window).y = y;
	(*window).renderer = new Cvs_Renderer(window);
	if(CV_GLOBALSTATEMACHINE.CheckSubSystem("Render_System"))
	{
		printf("Initialized new Render System renderer\n");
	}

	return &windows[name];
}

int CVS_Window::getWidth()
{
	return w;
}

int CVS_Window::getHeight()
{
	return h;
}
