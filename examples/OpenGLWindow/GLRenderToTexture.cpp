#ifndef NO_OPENGL3

///See http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-14-render-to-texture/

#include "GLRenderToTexture.h"
#include "Bullet3Common/b3Scalar.h"  // for b3Assert
#include <string.h>
#include <stdio.h>

bool gIntelLinuxglDrawBufferWorkaround = false;

GLRenderToTexture::GLRenderToTexture()
	: m_framebufferName(0)
{
#if !defined(_WIN32) && !defined(__APPLE__)
	const GLubyte* ven = glGetString(GL_VENDOR);
	printf("ven = %s\n", ven);

/// [IGE]: fix compare with short vender's name
	if (ven != NULL && strlen((const char*)ven) >=5 && strncmp((const char*)ven, "Intel", 5) == 0)
	{
		printf("Workaround for some crash in the Intel OpenGL driver on Linux/Ubuntu\n");
		gIntelLinuxglDrawBufferWorkaround = true;
	}
/// [/IGE]

/// [IGE]: Fix GLES
	// Force workaround on OpenGLES devices
	#ifdef GLAD_GLES2
		gIntelLinuxglDrawBufferWorkaround = true;
	#endif
/// [/IGE]
#endif  //!defined(_WIN32) && !defined(__APPLE__)
}

void GLRenderToTexture::init(int width, int height, GLuint textureId, int renderTextureType)
{
	m_renderTextureType = renderTextureType;

	glGenFramebuffers(1, &m_framebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferName);

	// The depth buffer
	//	glGenRenderbuffers(1, &m_depthrenderbuffer);

	//	glBindRenderbuffer(GL_RENDERBUFFER, m_depthrenderbuffer);
	//	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	//	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthrenderbuffer);

	switch (m_renderTextureType)
	{
		case RENDERTEXTURE_COLOR:
		{
/// [IGE]: Fix GLES
#ifdef GLAD_GLES2
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId, 0);
#else
			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureId, 0);
#endif
/// [/IGE]
			break;
		}
		case RENDERTEXTURE_DEPTH:
		{
/// [IGE]: Fix GLES
#ifdef GLAD_GLES2
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, textureId, 0);
#else
			glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, textureId, 0);
#endif
/// [/IGE]
			break;
		}
		default:
		{
			b3Assert(0);
		}
	};

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

bool GLRenderToTexture::enable()
{
	bool status = false;

	glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferName);

	switch (m_renderTextureType)
	{
		case RENDERTEXTURE_COLOR:
		{
			// Set the list of draw buffers.
			GLenum drawBuffers[2] = {GL_COLOR_ATTACHMENT0, 0};
			glDrawBuffers(1, drawBuffers);
			break;
		}
		case RENDERTEXTURE_DEPTH:
		{
			//Intel OpenGL driver crashes when using GL_NONE for glDrawBuffer on Linux, so use a workaround
			if (gIntelLinuxglDrawBufferWorkaround)
			{
				GLenum drawBuffers[2] = {GL_COLOR_ATTACHMENT0, 0};
				glDrawBuffers(1, drawBuffers);
			}
			else
			{
				glDrawBuffer(GL_NONE);
			}
			break;
		}
		default:
		{
			b3Assert(0);
		}
	};

	// Always check that our framebuffer is ok
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
	{
		status = true;
	}

	return status;
}

void GLRenderToTexture::disable()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLRenderToTexture::~GLRenderToTexture()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	if (m_depthrenderbuffer)
	{
		glDeleteRenderbuffers(1, &m_depthrenderbuffer);
	}

	if (m_framebufferName)
	{
		glDeleteFramebuffers(1, &m_framebufferName);
	}
}
#endif
