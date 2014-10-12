#include "Canvas.h"

bool CVS_Initialized = false;

CANVAS_STATEMACHINE CV_GLOBALSTATEMACHINE;

bool CANVAS_STATEMACHINE::RequireSubSystem(std::string name, CVS_App* instance)
{
	for(int i = 0; i < this->SubSystems.size(); ++i)
	{
		if(SubSystems[i].name == name)
		{
			return SubSystems[i].InitializeSubSystem(instance);
		}
	}
	return false;
}

bool CANVAS_STATEMACHINE::CheckSubSystem(std::string name)
{
	for(int i = 0; i < this->SubSystems.size(); ++i)
	{
		if(SubSystems[i].name == name)
		{
			return SubSystems[i].system->initialized;
		}
	}
	return false;
}


bool RequireSubSystem(std::string name, CVS_App* instance)
{
	return CV_GLOBALSTATEMACHINE.RequireSubSystem(name, instance);
}

CVS_App::CVS_App()
{
}

bool CVS_App::InitializeApp()
{
	return true;
}

void CVS_App::Run()
{

}

bool CVS_App::End()
{
	return true;
}

CVS_App::~CVS_App()
{
}



/********************************
Editor App
********************************/
Editor::Editor(){
	//Set our app type to two, which is registered as 2.
	AppType = 2;
	if(!CVS_Initialized)
	{
		addAndPrintErrorMessage("CVS has not been properly initaized!\n");
		return;
	}
	RequireSubSystem("Render_System", this);
	window = CV_GLOBALSTATEMACHINE.m_windowManager.CreateNewWindow("Canvas Editor", 0, 0, 1980, 980);
	SDL_SetWindowMaximumSize(window->windowHandler, 1980, 1080);
	SDL_MaximizeWindow(window->windowHandler);
};

bool Editor::InitializeApp(){
	return true;
}

void Editor::Run(){
	while(true)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_Event e;
		while(SDL_PollEvent(&e) > 0)
		{

		}
		SDL_GL_SwapWindow(window->windowHandler);
	}
}

bool Editor::End(){
	return false;
}

Editor::~Editor(){

}

bool RegisterSubSystem(std::string subsystemname, Cvs_SubSys* system)
{
	//Begin a registration
	SubSystemRegistration regi;
	//Set registration parameters.
	regi.name = subsystemname;
	regi.hashID = CV_GLOBALSTATEMACHINE.SubSystems.size();
	regi.system = system;
	//Store registration.
	CV_GLOBALSTATEMACHINE.SubSystems.push_back(regi);
	return true;
}

void addAndPrintErrorMessage(const char* error)
{
	printf("%s\n", error);
	CV_GLOBALSTATEMACHINE.ErrorLogStream.push_back(cvstr(error));
}

bool CVS_Initialize()
{
	printf("Initialize CVS\n");
	if(CVS_Initialized)
		return true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		addAndPrintErrorMessage(SDL_GetError());
		return false;
	}
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);	

	int imgFlags = IMG_INIT_PNG;

	if( !(IMG_Init( imgFlags ) & imgFlags))
	{
		addAndPrintErrorMessage(IMG_GetError());
		return false;
	}
	RegisterSubSystem("Render_System", new Cvs_RenderSystem());
	CVS_Initialized = true;
	printf("Initialized CVS\n");
	return true;
}