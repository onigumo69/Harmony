#pragma once

#include "Harmony/Renderer/Texture.h"

#include <glad/glad.h>

namespace Harmony
{

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t get_width() const override { return _width; }
		virtual uint32_t get_height() const override { return _height; }
		virtual uint32_t get_renderer_id() const override { return _renderer_id; }

		virtual void set_data(void* data, uint32_t size) override;

		virtual void bind(uint32_t slot = 0) const override;

		virtual bool operator==(const Texture& other) const override
		{
			return _renderer_id == ((OpenGLTexture2D&)other)._renderer_id;
		}
	private:
		std::string _path;
		uint32_t _width, _height;
		uint32_t _renderer_id;
		GLenum _internal_format, _data_format;
	};

}