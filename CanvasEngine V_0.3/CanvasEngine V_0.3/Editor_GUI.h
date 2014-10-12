#ifndef EDITOR_GUI_H
#define EDITOR_GUI_H

#include "CVS_GUI.h"

class Editor;

struct LayoutGUI;

struct handleBar:public cv_g_simpleElement{
	std::vector<int*> values;

	bool horizontal;
	bool movable;

	bool onDrag;
	int lastX, lastY;

	handleBar(int v, bool horizontalOrientation, handleBar* bar1, handleBar* bar2, LayoutGUI* parent, Cvs_Window* window);
	handleBar(int type, LayoutGUI* parent, Cvs_Window* window);

	virtual void onHover();
	virtual void onMouseDown();
	virtual void onMouseUp();
	virtual void offHover();
	virtual void Render(cv_2D_DrawProgram DrawTool, int x, int y);

	void move(int x, int y);

	void updatePosition();

	virtual void setUpperDelimiter(handleBar* bar);
	virtual void setLowerDelimiter(handleBar* bar);
	virtual void addInt(int* value);
};

struct LayoutGUI:public cv_g_Element{
	handleBar topBar, botBar, leftBar, rightBar;
	std::vector<handleBar*> divisors;
	LayoutGUI(float x, float y, float w, float h, cv_g_Element* parent, Cvs_Window* window);
	virtual handleBar* createNewHandleBar(handleBar* bar1, handleBar* bar2, int value);

	virtual bool getMouseDown(SDL_Event* e, int x, int y);
	virtual bool getMouseUp(SDL_Event* e, int x, int y);
	virtual bool getHover(SDL_Event* e, int x, int y);

	virtual void onHover();
	virtual void onMouseDown();
	virtual void onMouseUp();
	virtual void offHover();
	
	virtual void Render(cv_2D_DrawProgram DrawTool, int x, int y);

	virtual void setTopSet(handleBar* bar);
	virtual void setBotSet(handleBar* bar);
	virtual void setLeftSet(handleBar* bar);
	virtual void setRightSet(handleBar* bar);
};

struct windowTopFrame:public cv_g_simpleElement{

	windowTopFrame(Cvs_Window* window);

	virtual bool onMouseDown(SDL_Event* e, int x, int y);
	virtual bool onMouseUp(SDL_Event* e, int x, int y);
	virtual bool onHover(SDL_Event* e, int x, int y);
	virtual void offHover();
	virtual void Render(cv_2D_DrawProgram DrawTool, int x, int y);

};

struct QuitButton:public cv_g_simpleElement{
	QuitButton(bool* quitBool);

	virtual void onMouseDown();
	virtual void onMouseUp();
	virtual void onHover();
	virtual void offHover();
	virtual void Render(cv_2D_DrawProgram DrawTool, int x, int y);
};

struct SceneRenderer:public cv_g_simpleElement{
public:
	Cvs_Renderer* renderer;
	SceneRenderer(Cvs_Renderer* renderer,int x, int y, int w, int h);

	virtual bool getMouseDown(SDL_Event* e, int x, int y);
	virtual bool getMouseUp(SDL_Event* e, int x, int y);
	virtual bool onHover(SDL_Event* e, int x, int y);
	virtual void offHover();
	virtual void Render(cv_2D_DrawProgram DrawTool, int x, int y);
};

struct EditorGUI:public LayoutGUI{
public:
	Editor* editor;
	EditorGUI(int screenWidth, int screenHeight);

	virtual bool getMouseDown(SDL_Event* e, int x, int y);
	virtual bool getMouseUp(SDL_Event* e, int x, int y);
	virtual bool onHover(SDL_Event* e, int x, int y);
	virtual void offHover();
	virtual void Render(cv_2D_DrawProgram DrawTool, int x, int y);

	void setTopSet(handleBar* bar);
	void setBotSet(handleBar* bar);
	void setLeftSet(handleBar* bar);
	void setRightSet(handleBar* bar);
};



#endif