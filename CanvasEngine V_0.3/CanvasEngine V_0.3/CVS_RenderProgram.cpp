#include "CVS_RenderSystem.h"
#include "CVS_Window.h"

GLuint compileShader(char* vertex_file_path, char* fragment_file_path)
{
	// Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
 
    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if(VertexShaderStream.is_open())
    {
        std::string Line = "";
        while(getline(VertexShaderStream, Line))
            VertexShaderCode += "\n" + Line;
        VertexShaderStream.close();
    }

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if(FragmentShaderStream.is_open()){
        std::string Line = "";
        while(getline(FragmentShaderStream, Line))
            FragmentShaderCode += "\n" + Line;
        FragmentShaderStream.close();
    }
 
    GLint Result = GL_FALSE;
    int InfoLogLength;
 
    // Compile Vertex Shader
    printf("Compiling shader : %s\n", vertex_file_path);
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);
 
    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> VertexShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
    fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);
 
    // Compile Fragment Shader
    printf("Compiling shader : %s\n", fragment_file_path);
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);
 
    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
    fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);
 
    // Link the program
    fprintf(stdout, "Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);
 
    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> ProgramErrorMessage( std::max(InfoLogLength, int(1)) );
    glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
    fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
 
    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

	return ProgramID;
	glUseProgram(0);
}

cv_ShaderProgram::cv_ShaderProgram(std::string name, char* vertpath, char* fragpath):name(name), vertPath(vertpath),fragPath(fragpath)
{
}

cv_ShaderProgram::~cv_ShaderProgram()
{
}

cv_ShaderProgram cv_2D_DrawProgram::cvTextShaderProgram("2Dtexture", "./shaders/2D/2D.vert", "./shaders/2D/2Dtexture.frag");
cv_ShaderProgram cv_2D_DrawProgram::cvColorShaderProgram("2Dtexture", "./shaders/2D/2D.vert", "./shaders/2D/2D.frag");

cv_2D_DrawProgram::cv_2D_DrawProgram(Cvs_Renderer* renderer, int screenWidth, int screenHeight)
{

	
}

void cv_2D_DrawProgram::process2DShaders()
{

}


void cv_2D_DrawProgram::initialize2DShaders()
{

}

void cv_2D_DrawProgram::drawTextureRect(cv_Texture* texture, int x, int y, int w, int h)
{
	int windowWidth = renderer->window->getWidth();
	int windowHeight = renderer->window->getHeight();
	glm::mat4 scale = glm::ortho<float> (-windowWidth/2, windowWidth/2, -windowHeight/2, windowHeight/2, -10, 10);
	x -= windowWidth/2;
	y -= windowHeight/2;


}

void cv_2D_DrawProgram::drawColorRect(cv_Color texture, int x, int y, int w, int h)
{

}