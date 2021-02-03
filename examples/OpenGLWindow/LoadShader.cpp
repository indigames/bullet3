#include "LoadShader.h"
#include "OpenGLInclude.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string> /// [IGE]: add for string manipulation

// Load the shader from the source text
void gltLoadShaderSrc(const char *szShaderSrc, GLuint shader)
{
	GLchar *fsStringPtr[1];

	fsStringPtr[0] = (GLchar *)szShaderSrc;
	glShaderSource(shader, 1, (const GLchar **)fsStringPtr, NULL);
}

GLuint gltLoadShaderPair(const char *szVertexProg, const char *szFragmentProg)
{
	assert(glGetError() == GL_NO_ERROR);

	// Temporary Shader objects
	GLuint hVertexShader;
	GLuint hFragmentShader;
	GLuint hReturn = 0;
	GLint testVal;

	// Create shader objects
	hVertexShader = glCreateShader(GL_VERTEX_SHADER);
	hFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

/// [IGE]: Fix GLES
#ifdef GLAD_GLES2
	const auto strToFind150 = std::string("#version 150");
	const auto strToFind330Core = std::string("#version 330 core");
	const auto strToFind330 = std::string("#version 330");
	const auto strToReplace = std::string("#version 300 es\nprecision highp float;\nprecision highp sampler2DShadow;");
	auto vShader = std::string(szVertexProg);
	auto hShader = std::string(szFragmentProg);

	// Find #150
	auto idx = vShader.find(strToFind150);
	if(idx != std::string::npos)
		vShader.replace(idx, strToFind150.length(), strToReplace);

	idx = hShader.find(strToFind150);
	if(idx != std::string::npos)
		hShader.replace(idx, strToFind150.length(), strToReplace);

	// Find 330 core
	idx = vShader.find(strToFind330Core);
	if(idx != std::string::npos)
		vShader.replace(idx, strToFind330Core.length(), strToReplace);

	idx = hShader.find(strToFind330Core);
	if(idx != std::string::npos)
		hShader.replace(idx, strToFind330Core.length(), strToReplace);

	// Find 330
	idx = vShader.find(strToFind330);
	if(idx != std::string::npos)
		vShader.replace(idx, strToFind330.length(), strToReplace);

	idx = hShader.find(strToFind330);
	if(idx != std::string::npos)
		hShader.replace(idx, strToFind330.length(), strToReplace);

	// Load shader
	gltLoadShaderSrc(vShader.c_str(), hVertexShader);
	gltLoadShaderSrc(hShader.c_str(), hFragmentShader);
#else
	gltLoadShaderSrc(szVertexProg, hVertexShader);
	gltLoadShaderSrc(szFragmentProg, hFragmentShader);
#endif
/// [/IGE]

	// Compile them
	glCompileShader(hVertexShader);
	assert(glGetError() == GL_NO_ERROR);

	glGetShaderiv(hVertexShader, GL_COMPILE_STATUS, &testVal);
	if (testVal == GL_FALSE)
	{
		char temp[256] = "";
		glGetShaderInfoLog(hVertexShader, 256, NULL, temp);
		fprintf(stderr, "Compile failed:\n%s\n", temp);
		assert(0);
		return 0;
		glDeleteShader(hVertexShader);
		glDeleteShader(hFragmentShader);
		return (GLuint)0;
	}

	assert(glGetError() == GL_NO_ERROR);

	glCompileShader(hFragmentShader);
	assert(glGetError() == GL_NO_ERROR);

	glGetShaderiv(hFragmentShader, GL_COMPILE_STATUS, &testVal);
	if (testVal == GL_FALSE)
	{
		char temp[256] = "";
		glGetShaderInfoLog(hFragmentShader, 256, NULL, temp);
		fprintf(stderr, "Compile failed:\n%s\n", temp);
		assert(0);
		exit(EXIT_FAILURE);
		glDeleteShader(hVertexShader);
		glDeleteShader(hFragmentShader);
		return (GLuint)0;
	}

	assert(glGetError() == GL_NO_ERROR);

	// Check for errors

	// Link them - assuming it works...
	hReturn = glCreateProgram();
	glAttachShader(hReturn, hVertexShader);
	glAttachShader(hReturn, hFragmentShader);

	glLinkProgram(hReturn);

	// These are no longer needed
	glDeleteShader(hVertexShader);
	glDeleteShader(hFragmentShader);

	// Make sure link worked too
	glGetProgramiv(hReturn, GL_LINK_STATUS, &testVal);
	if (testVal == GL_FALSE)
	{
		GLsizei maxLen = 4096;
		GLchar infoLog[4096];
		GLsizei actualLen;

		glGetProgramInfoLog(hReturn,
							maxLen,
							&actualLen,
							infoLog);

		printf("Warning/Error in GLSL shader:\n");
		printf("%s\n", infoLog);
		glDeleteProgram(hReturn);
		return (GLuint)0;
	}

	return hReturn;
}
