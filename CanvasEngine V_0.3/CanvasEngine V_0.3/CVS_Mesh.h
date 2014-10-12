#ifndef CVS_MESH_H
#define CVS_MESH_H
#include "Canvas_PreCompiled.h"
#include "CVS_Math.h"

struct Vertex{
	cvvec3 position;
	cvvec2 uv;
	cvvec3 normal;
	cvivec4 weight;
	cvmat4 bonetransform;
};

struct Vertex_Weights{
	unsigned int Index;
	float weight;
};

struct Cvs_Bone{
	Cvs_Bone* parent;
	std::vector<Cvs_Bone*> children;
	float length;
	cvmat4 boneMatrix;
	std::vector<Vertex_Weights> weights;
	void deleteAllBones();
};

struct Mesh{
	std::vector<Vertex> vertices;
	Cvs_Bone* root;
};


#endif