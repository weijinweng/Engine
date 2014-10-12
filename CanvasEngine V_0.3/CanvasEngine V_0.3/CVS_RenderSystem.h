#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H
#include "CanvasSubSystem.h"
#include "CVS_Mesh.h"
#include "CVS_Camera.h"
#include "CVS_RenderProgram.h"

struct RenderNode;
class CVS_Window;

struct RenderProgramRef{
	cv_ShaderProgram* program;
	std::vector<RenderNode*> m_ChildNodes;
public:
	void addChild(RenderNode* child);
};

struct RDS_TextureRef{
	
};

struct RDS_transformNode{
	cv_Transform transform;
};

struct RDS_RenderNode{
public:
};

class Scene{
public:

	std::vector<RenderProgramRef> m_RenderPrograms;
	std::vector<RenderNode*> m_RenderNodes;
	RDS_transformNode m_root;

	bool changeRenderMethod(CV_Enum method);
	void render();
	Cvs_Camera* addCamera();
};


class Cvs_Renderer{
public:
	//Responsible for a specific window's rendering. Can draw 2D guis, but require a RenderSystem before 3D Apps.
	SDL_GLContext glContext;
	//2D draw tools
	cv_2D_DrawProgram* m_2DShader;
	CVS_Window* window;
	Scene* m_scene;
	Cvs_Renderer(CVS_Window* windowHandler);

	void setScene(Scene* scene);
	void removeScene(Scene* scene);

	void DrawRect(int x, int y, int w, int h);
	void setRenderSystem(Cvs_RenderSystem* system);
	void setViewPort(int x, int y, int w, int h);
	void setAsCurrentRenderSystem();
	void SwapBuffers();
	void setRenderTarget(cv_Texture* texture, CV_Enum componentEnum);
	//Set draw mode.
	void enableDrawMode(unsigned short drawMode);
	//Set test.
	void testMode(unsigned short mode);
	void setTestFunc(CV_Enum mode, CV_Enum func);
	//Draw functions. 
	void drawSettings(unsigned short settings);
	void drawTexture(cv_Texture texture, int x, int y, int width, int height);
	~Cvs_Renderer();
};

/*
*This is the subsystem that manages all renderer related matters. A Cvs_Renderer 
*can exist without one, but it can not perform higher level functions such as 3D apps.
*/
struct Cvs_RenderSystem:Cvs_SubSys{
public:
	std::vector<Mesh*> meshes;
	std::vector<cv_Texture*> textures;
	//Keeps track of Scenes
	std::vector<Scene> scenes;
	//Keeps track of all renderers in its control.
	std::vector<Cvs_Renderer*> renderers;
	Cvs_RenderSystem();
	//Initialized the app, requires all app windows.
	bool initialize(CVS_App* instance);
	bool end();

};


#endif