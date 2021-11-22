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
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertexData2), this->vertexData2, GL_STATIC_DRAW);

	/*
		glBufferData 사용 시 두번째 파라미터는 sizeof(vertexData)
		vertexData 는 GLfloat Type으로 9개의 데이터가 들어있다.
		4바이트 * 9 = 36 바이트를 처리한다.
		*/
}


void GLManager::GenBuffer(std::vector<GLfloat>& vtx)
{
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vtx.size(), vtx.data(), GL_STATIC_DRAW);

	/*
		glBufferData 사용 시 두번째 파라미터는 sizeof(vertexData)
		vertexData 는 GLfloat Type으로 9개의 데이터가 들어있다.
		4바이트 * 9 = 36 바이트를 처리한다.
		*/
}

void GLManager::UseProgram()
{
	glUseProgram(this->program);
}

void GLManager::Attribute(GLfloat vertexData[])
{
	glBindBuffer(GL_ARRAY_BUFFER, this->vtx_buf);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertexData2), this->vertexData2, GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, this->vtx_buf);
	this->vtx_ary = glGetAttribLocation(program, "myVertex");
	glEnableVertexAttribArray(this->vtx_ary);
	glVertexAttribPointer(this->vtx_ary, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void GLManager::Attribute(std::vector<GLfloat>& vtx, bool t)
{
	this->vtx_ary = glGetAttribLocation(program, "myVertex");
	glEnableVertexAttribArray(this->vtx_ary);
	glVertexAttribPointer(this->vtx_ary, 3, GL_FLOAT, GL_FALSE, 0, (const void *)0);
}

GLint GLManager::Uniform(const char* name, const GLfloat * transformationMatrix)
{
	GLint uniformLoc = glGetUniformLocation(program, name);
	glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, transformationMatrix);

	return uniformLoc;
}

void GLManager::Draw(int size)
{
	glDrawArrays(GL_TRIANGLES, 0, size);
	glDisableVertexAttribArray(this->vtx_ary);
	
}
