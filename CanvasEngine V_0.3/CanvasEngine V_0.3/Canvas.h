#ifndef CANVAS_H
#define CANVAS_H

#include "CVS_Window.h"

/*
Template for an Canvas application.
*/
class CVS_App{
public:
	int AppType;
	CVS_App();
	virtual bool InitializeApp();
	virtual void Run();
	virtual bool End();
	~CVS_App();
};


/*
Canvas editor.
*/
class Editor:public CVS_App{
public:
	CVS_Window* window;
	Editor();
	virtual bool InitializeApp();
	virtual void Run();
	virtual bool End();
	~Editor();
};

typedef std::string cvstr;

struct CANVAS_STATEMACHINE{
	std::vector<cvstr> ErrorLogStream;
	std::vector<SubSystemRegistration> SubSystems;

	bool RequireSubSystem(std::string name, CVS_App* instance);
	bool CheckSubSystem(std::string subsystem);
	Cvs_WindowManager m_windowManager;
};

/* 
Adds an error message to log and print at the same time
*/
void addAndPrintErrorMessage(const char* error);
bool RequireSubSystem(std::string systemname, CVS_App* instance);
bool CVS_Initialize();
bool RegisterSubSystem(std::string subsystem, Cvs_SubSys* systemInstance);

#endif