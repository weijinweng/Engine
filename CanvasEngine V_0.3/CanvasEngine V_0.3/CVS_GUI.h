#ifndef CVS_GUI_H
#define CVS_GUI_H
#include "Canvas_PreCompiled.h"
#include "CVS_RenderSystem.h"

class Cvs_Window;

struct cv_g_Element;

struct cv_g_Rect{
	int x,y,w,h;
};

struct iAABB{
	int maxX, minX, maxY, minY;
};

struct cv_g_Properties{
	cv_TextureRef BackGroundImage;
	cv_Color color;
	iAABB aabb;

	float borderRadius;
};

struct cv_g_simpleElement{
public:
	cv_g_Element* parent;
	cv_g_Properties properties;
	Cvs_Window* window;

	cv_g_simpleElement(int x, int y, int w, int h, cv_g_Element* parent, Cvs_Window* window);
	
	//Mouse delegation functions.
	virtual bool getMouseDown(SDL_Event* e, int x, int y);
	virtual bool getMouseUp(SDL_Event* e, int x, int y);
	virtual bool getHover(SDL_Event* e, int x, int y);

	//Input response functions
	virtual void onHover();
	virtual void onMouseDown();
	virtual void onMouseUp();
	virtual void offHover();

	virtual void Render(cv_2D_DrawProgram DrawTool, int x, int y);
};

struct cv_g_Element:public cv_g_simpleElement{
	std::vector<cv_g_simpleElement*> children;

	cv_g_Element(int x, int y, int w, int h, cv_g_Element* parent, Cvs_Window* window);

	//Mouse delegation functions.
	virtual bool getMouseDown(SDL_Event* e, int x, int y);
	virtual bool getMouseUp(SDL_Event* e, int x, int y);
	virtual bool getHover(SDL_Event* e, int x, int y);

	//Input response functions
	virtual void onHover();
	virtual void onMouseDown();
	virtual void onMouseUp();
	virtual void offHover();

	virtual void Render(cv_2D_DrawProgram DrawTool, int x, int y);
};

bool checkMouseOver(iAABB aabb, int x, int y);

#endif