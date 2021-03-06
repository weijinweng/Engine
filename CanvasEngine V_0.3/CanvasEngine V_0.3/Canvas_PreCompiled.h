#ifndef CVS_PRECOMPILED
#define CVS_PRECOMPILED

//SDL for window creation and Event handling.
//STL externals
#include <stdio.h>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>

//SDL supplements and extensions
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_thread.h>
#include <SDL_syswm.h>
#undef main

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
	//Windows only API
	#include <Windows.h>
	#include <dwmapi.h>
#endif

//GLEW for opengl
#include <gl\glew.h>
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\quaternion.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtx\simd_mat4.hpp"
#include "glm\gtx\simd_quat.hpp"
#include "glm\gtx\simd_vec4.hpp"

//Assimp for static files
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>
#include <assimp\scene.h>

//FBX for autodesk formats.
#include <fbxsdk.h>



enum CV_Enum{
	CVS_NULL = 0,
	CVS_RDS_DEFERRED = 3,
	CVS_RDS_FORWARD = 5,
	CVS_RDS_NONE = 6,
	CVS_RDS_
};

#endif