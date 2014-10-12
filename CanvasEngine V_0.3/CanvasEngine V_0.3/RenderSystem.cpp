#include "CVS_RenderSystem.h"
#include "Canvas.h"

Cvs_Renderer::Cvs_Renderer(CVS_Window* windowHandler){
	glContext = SDL_GL_CreateContext(windowHandler->windowHandler);

	if (glContext == NULL)
	{
		printf("OpenGl context could not be created! SDL Error: %s\n", SDL_GetError());
		return;
	}else
	{
		glewExperimental = GL_TRUE;
		GLenum glewError = glewInit();
		if (glewError != GLEW_OK)
		{
			printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
		}
		if (SDL_GL_SetSwapInterval(0) < 0)
		{
			printf("Error setting swap interval %s\n", SDL_GetError());
		}
	}
	glClearColor( 0.0f, 0.0f, 0.5f, 1.0f);
	SDL_GL_SwapWindow(windowHandler->windowHandler);

	int ScreenWidth, ScreenHeight;

	SDL_GetWindowSize(windowHandler->windowHandler, &ScreenWidth, &ScreenHeight);

	this->m_2DShader = new cv_2D_DrawProgram(this, ScreenWidth, ScreenHeight );

	printf("Renderer glContext initialized\n");
}

Cvs_Renderer::~Cvs_Renderer()
{
	delete m_2DShader;
}

Cvs_RenderSystem::Cvs_RenderSystem(){

	printf("Render System created\n");
}

bool Cvs_RenderSystem::initialize(CVS_App* appInstance){
	switch(appInstance->AppType)
	{
	case 2:
		printf("Initialized RenderSystem in editor app\n");
		initialized = true;
		return true;
	default:
		addAndPrintErrorMessage("Unrecognized CVS_App!\n");
	}
}


/*
*Take care of all resources
*/
bool Cvs_RenderSystem::end(){
	return true;
}
