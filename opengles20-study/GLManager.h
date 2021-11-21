#pragma once
#define DYNAMICGLES_NO_NAMESPACE
#define DYNAMICEGL_NO_NAMESPACE
#include <DynamicGles.h>


const char * const sfrag_shader_src = "\
											 void main (void)\
											 {\
												gl_FragColor = vec4(1.0, 1.0, 0.66 ,1.0);\
											 }";

const char * const svtx_shader_src = "\
										   attribute highp vec4	myVertex;\
										   uniform highp mat4 transformationMatrix;\
										   void main(void)\
										   {\
										   gl_Position = transformationMatrix * myVertex;\
										   }";



class GLManager
{
public:
	GLManager(const char* vtx_shader_src, const char* frag_shader_src);
	~GLManager();
	void GenBuffer();
	void UseProgram();
	void Attribute(GLfloat vertexData[]);
	GLint Uniform(const char* name, const GLfloat* transformationMatrix);
	void Draw();


	const GLfloat vertexData[9] = { 
		-0.4f, -0.4f, 0.0f,
		0.4f, -0.4f, 0.0f, 
		0.0f, 0.4f, 0.0f 
	}; 


	GLuint program;
	GLuint vtx_buf;
	GLuint frag_buf;
	GLuint vary;
	GLuint vtx_ary;

private:

	const char* vtx_shader_src;
	const char* frag_shader_src;

};

