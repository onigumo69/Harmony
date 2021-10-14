#include "OpenGLFramebuffer.h"

#include "Harmony/Core/Core.h"

#include <glad/glad.h>

namespace Harmony
{

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec)
		: _specification(spec)
	{
		invalidate();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &_renderer_id);
		glDeleteTextures(1, &_color_attachment);
		glDeleteTextures(1, &_depth_attachment);
	}

	void OpenGLFramebuffer::invalidate()
	{
		if (_renderer_id)
		{
			glDeleteFramebuffers(1, &_renderer_id);
			glDeleteTextures(1, &_color_attachment);
			glDeleteTextures(1, &_depth_attachment);
		}

		glCreateFramebuffers(1, &_renderer_id);
		glBindFramebuffer(GL_FRAMEBUFFER, _renderer_id);

		glCreateTextures(GL_TEXTURE_2D, 1, &_color_attachment);
		glBindTexture(GL_TEXTURE_2D, _color_attachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _specification.width, _specification.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _color_attachment, 0);

		glCreateTextures(GL_TEXTURE_2D, 1, &_depth_attachment);
		glBindTexture(GL_TEXTURE_2D, _depth_attachment);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, _specification.width, _specification.height);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, _depth_attachment, 0);

		//HM_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _renderer_id);
		glViewport(0, 0, _specification.width, _specification.height);
	}

	void OpenGLFramebuffer::unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::resize(uint32_t width, uint32_t height)
	{
		_specification.width = width;
		_specification.height = height;

		invalidate();
	}

}