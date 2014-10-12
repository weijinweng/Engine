#ifndef CVS_WINDOW_H
#define CVS_WINDOW_H

#include "CanvasSubSystem.h"
#include "CVS_RenderSystem.h"

struct CVS_Window{
	int x,y,w,h;
	SDL_Window* windowHandler;
	Cvs_Renderer* renderer;
	Cvs_WindowManager* manager;
public:
	int getWidth();
	int getHeight();
	int setWidth(int w);
	int setHeight(int h);
	int getX();
	int getY();
	int setX(int x);
	int setY(int y);
	void getMouseInWindow(int& x, int& y);
	Cvs_Renderer* getRenderer();
	CVS_Window* createChildWindow(std::string name, int x, int y, int w, int h);
};

class Cvs_WindowManager{
public:
	std::map<std::string, CVS_Window> windows;
	Cvs_WindowManager();
	CVS_Window* CreateNewWindow(std::string name, int x, int y, int w, int h);
};

#endif