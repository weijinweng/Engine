#ifndef CAMERA_H
#define CAMERA_H

#include "Canvas_PreCompiled.h"
#include "CVS_Math.h"

struct Cvs_Camera{
public:
	cv_Transform transform;
	cvmat4 Perspective;
	cvmat4 View;
	virtual cvmat4 getView();
	virtual cvmat4 getPerspective();
	virtual void getEvents(SDL_Event* e);
	void setPerspective(float FOV, float aspectRatio, float nearz, float farz);
	void setOrthographic(float minx, float maxx, float miny, float maxy, float minz, float maxz);
};

struct Cvs_fpsCamera: public Cvs_Camera{
};

struct Cvs_targetCamera: public Cvs_Camera{
	
};

#endif