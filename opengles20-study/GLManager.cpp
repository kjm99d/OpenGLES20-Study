#include "GLManager.h"

static volatile unsigned int program_count;

GLManager::GLManager(const char * vtx_shader_src, const char * frag_shader_src)
{
	InterlockedIncrement(&program_count);

	this->program = glCreateProgram();
	this->vtx_shader_src = vtx_shader_src;
	this->frag_shader_src = frag_shader_src;

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(fragmentShader, 1, (const char**)&this->frag_shader_src, NULL);
	glCompileShader(fragmentShader);
	// 쉐이더 컴파일 오류 체크 해야하는데 일단 패스

	glShaderSource(vertexShader, 1, (const char**)&this->vtx_shader_src, NULL);
	glCompileShader(vertexShader);

	glAttachShader(this->program, fragmentShader);
	glAttachShader(this->program, vertexShader);
	
	// Bind the vertex attribute "myVertex" to location VERTEX_ARRAY (0)
	// glBindAttribLocation(this->program, vary, "myVertex");
	glLinkProgram(this->program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	
}

GLManager::~GLManager()
{
}

void GLManager::GenBuffer()
{
	glGenBuffers(1, &this->vtx_buf);
	glBindBuffer(GL_ARRAY_BUFFER, this->vtx_buf);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
}

void GLManager::UseProgram()
{
	glUseProgram(this->program);
}

void GLManager::Attribute(GLfloat vertexData[])
{
	this->vtx_ary = glGetAttribLocation(program, "myVertex");
	glEnableVertexAttribArray(vtx_ary);
	glVertexAttribPointer(vtx_ary, 3, GL_FLOAT, GL_FALSE, 0, vertexData);
}

GLint GLManager::Uniform(const char* name, const GLfloat * transformationMatrix)
{
	GLint uniformLoc = glGetUniformLocation(program, name);
	glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, transformationMatrix);

	return uniformLoc;
}

void GLManager::Draw()
{
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(vtx_ary);
}
