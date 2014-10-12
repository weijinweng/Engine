#ifndef CVS_MATH_H
#define CVS_MATH_H
#include "Canvas_PreCompiled.h"

typedef glm::simdMat4 cvmat4;
typedef glm::simdVec4 cvvec4;
typedef glm::simdQuat cvquat;
typedef glm::vec3 cvvec3;
typedef glm::vec2 cvvec2;

struct cvivec4{
public:
	int i[4];
};

struct cv_Transform{
	cvvec3 position;
	cvquat rotation;
	cvvec3 scale;
	void lookAt(cvvec3 target);
	void rotateAround(cvvec3 point, float angle);
};

#endif