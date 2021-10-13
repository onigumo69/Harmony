#include "Harmony/Core/Core.h"
#include "Harmony/Core/Log.h"

#include "OpenGLTexture.h"

#include <glad/glad.h>

#include <stb_image.h>

namespace Harmony
{

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		: _width(width), _height(height)
	{
		_internal_format = GL_RGBA8;
		_data_format = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &_renderer_id);
		glTextureStorage2D(_renderer_id, 1, _internal_format, _width, _height);

		glTextureParameteri(_renderer_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(_renderer_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(_renderer_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(_renderer_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

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

		_internal_format = internal_format;
		_data_format = data_format;

		HM_CORE_ASSERT(internal_format & data_format, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &_renderer_id);
		glTextureStorage2D(_renderer_id, 1, internal_format, _width, _height);

		glTextureParameteri(_renderer_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(_renderer_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(_renderer_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(_renderer_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(_renderer_id, 0, 0, 0, _width, _height, data_format, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &_renderer_id);
	}

	void OpenGLTexture2D::set_data(void* data, uint32_t size)
	{
		uint32_t bpp = _data_format == GL_RGBA ? 4 : 3;
		HM_CORE_ASSERT(size == _width * _height * bpp, "Data must be entire texture!");
		glTextureSubImage2D(_renderer_id, 0, 0, 0, _width, _height, _data_format, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, _renderer_id);
	}
}