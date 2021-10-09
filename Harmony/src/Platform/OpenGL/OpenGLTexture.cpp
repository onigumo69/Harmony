#include "Harmony/Core.h"
#include "Harmony/Log.h"

#include "OpenGLTexture.h"

#include <glad/glad.h>

#include <stb_image.h>

namespace Harmony
{

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: _path(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		HM_CORE_ASSERT(data, "Failed to load image!");
		_width = width;
		_height = height;

		glCreateTextures(GL_TEXTURE_2D, 1, &_renderer_id);
		glTextureStorage2D(_renderer_id, 1, GL_RGB8, _width, _height);

		glTextureParameteri(_renderer_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(_renderer_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(_renderer_id, 0, 0, 0, _width, _height, GL_RGB, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &_renderer_id);
	}

	void OpenGLTexture2D::bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, _renderer_id);
	}
}