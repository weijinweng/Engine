#ifndef CVS_SUBSYSTEM_H
#define CVS_SUBSYSTEM_H
#include "Canvas_PreCompiled.h"


class CVS_App;

class Cvs_SubSys{
public:
	unsigned short systemType;
	bool initialized;
	Cvs_SubSys();
	virtual bool initialize(CVS_App* appInstance);
	virtual bool end();
	~Cvs_SubSys();
};

class Cvs_World;
class Cvs_RenderSystem;
class Cvs_Physics;
class Cvs_WindowManager;

struct SubSystemRegistration{
	Cvs_SubSys* system;
	unsigned short hashID;
	std::string name;
	Cvs_SubSys* getSubSystem();
	bool InitializeSubSystem(CVS_App* appInstance);
};

#endif