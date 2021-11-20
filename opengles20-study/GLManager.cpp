#include "GLManager.h"


static const char* const sfrag_shader_src = "\
											 void main (void)\
											 {\
												gl_FragColor = vec4(1.0, 1.0, 0.66 ,1.0);\
											 }";

static const char* const svtx_shader_src = "\
										   attribute highp vec4	myVertex;\
										   uniform highp mat4 transformationMatrix;\
										   void main(void)\
										   {\
										   gl_Position = transformationMatrix * myVertex;\
										   }";

GLManager::GLManager(const char* vtx_shader_src, const char* frag_shader_src)
{
	this->program = glCreateProgram();
	//this->vtx_shader_src = vtx_shader_src;
	//this->frag_shader_src = frag_shader_src;

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(fragmentShader, 1, (const char**)&sfrag_shader_src, NULL);
	glCompileShader(fragmentShader);
	// 쉐이더 컴파일 오류 체크 해야하는데 일단 패스

	glShaderSource(vertexShader, 1, (const char**)&svtx_shader_src, NULL);
	glCompileShader(vertexShader);

	glAttachShader(this->program, fragmentShader);
	glAttachShader(this->program, vertexShader);
	
	// Bind the vertex attribute "myVertex" to location VERTEX_ARRAY (0)
	glBindAttribLocation(this->program, vary, "myVertex");

	// Link the program
	glLinkProgram(this->program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	
}

GLManager::~GLManager()
{
}

void GLManager::GenBuffer()
{
	

	// Generate a buffer object
	glGenBuffers(1, &this->vtx_buf);

	// Bind buffer as an vertex buffer so we can fill it with data
	glBindBuffer(GL_ARRAY_BUFFER, this->vtx_buf);

	//	Set the buffer's size, data and usage
	//	Note the last argument - GL_STATIC_DRAW. This tells the driver that we intend to read from the buffer on the GPU, and don't intend
	//	to modify the data until we're done with it.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
}

void GLManager::UseProgram()
{
	glUseProgram(this->program);
}
