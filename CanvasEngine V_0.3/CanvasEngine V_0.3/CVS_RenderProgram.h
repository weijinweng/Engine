#ifndef CVS_RENDERPROGRAM_H
#define CVS_RENDERPROGRAM_H
#include "Canvas_PreCompiled.h"

class Cvs_Renderer;

struct cv_Color{
	float r,g,b,a;
};

struct cv_Texture{
	GLuint textureID;
	unsigned int textureIndex;
	cv_Texture();
	std::string filepath;
	std::string name;
	void loadFile(char* filepath);
	void textureData(int width, int height, void* pixelData, CV_Enum TextureType);
	void empty();
	void setTextureFilterMode(CV_Enum filterType, CV_Enum filterMode);
	~cv_Texture();
};

struct cv_TextureRef{
	cv_Texture* texture;
	bool hasTexture;
	void setTexture(cv_Texture* texture);
};

struct shaderValues{
	CV_Enum type;
	GLuint location;
};


struct cv_ShaderProgram{
	GLuint ShaderID;
	std::string name;
	std::string vertPath;
	std::string fragPath;
	std::vector<shaderValues> locations;
	cv_ShaderProgram(std::string name, char* vertpath, char* fragpath);
	void Recompile();
	void ChangeProgram();
	void BindProgram();
	void LoadNewFiles(char* vertpath, char* fragpath);
	void empty();
	~cv_ShaderProgram();
};

struct textDrawer{
	static GLuint textProgramID;
	void drawText(std::string text, int x, int y, int w, int h);
	void setDrawMethods(CV_Enum method);
};

struct cv_2D_DrawProgram{
	static cv_ShaderProgram cvTextShaderProgram;
	static cv_ShaderProgram cvColorShaderProgram;
	static cv_Texture rendertarget;
	Cvs_Renderer* renderer;

	cv_2D_DrawProgram(Cvs_Renderer* renderer, int screenWidth, int screenHeight);
	void process2DShaders();
	void initialize2DShaders();
	void drawTextureRect(cv_Texture* texture, int x, int y, int w, int h);
	void drawColorRect(cv_Color color, int x, int y, int w, int h);
};

#endif