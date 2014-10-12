#include "CanvasSubSystem.h"


Cvs_SubSys::Cvs_SubSys():initialized(false),systemType(0){
}

bool Cvs_SubSys::initialize(CVS_App* instance)
{
	return true;
}

bool Cvs_SubSys::end()
{
	return true;
}

Cvs_SubSys::~Cvs_SubSys()
{
	end();
}

bool SubSystemRegistration::InitializeSubSystem(CVS_App* appInstance)
{
	printf("Initializing subsystem %s\n", name.c_str());
	return system->initialize(appInstance);
}