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

		GLenum internal_format = 0, data_format = 0;
		if (channels == 4)
		{
			internal_format = GL_RGBA8;
			data_format = GL_RGBA;
		}
		else if (channels == 3)
		{
			internal_format = GL_RGB8;
			data_format = GL_RGB;
		}

		HM_CORE_ASSERT(internal_format & data_format, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &_renderer_id);
		glTextureStorage2D(_renderer_id, 1, internal_format, _width, _height);

		glTextureParameteri(_renderer_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(_renderer_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(_renderer_id, 0, 0, 0, _width, _height, data_format, GL_UNSIGNED_BYTE, data);

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