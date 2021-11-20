#pragma once
#define DYNAMICGLES_NO_NAMESPACE
#define DYNAMICEGL_NO_NAMESPACE
#include <DynamicGles.h>



class GLManager
{
public:
	GLManager(const char* vtx_shader_src, const char* frag_shader_src);
	~GLManager();
	void GenBuffer();
	void UseProgram();
	//void Attribute(GLfloat vertexData[]);
	//void Draw();


	const GLfloat vertexData[9] = { 
		-0.4f, -0.4f, 0.0f,
		0.4f, -0.4f, 0.0f, 
		0.0f, 0.4f, 0.0f 
	}; 


	GLuint program;
	GLuint vtx_buf;
	GLuint frag_buf;
	GLuint vary;

private:

	const char* vtx_shader_src;
	const char* frag_shader_src;

};

