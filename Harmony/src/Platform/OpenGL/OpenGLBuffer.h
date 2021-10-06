#pragma once

#include "Harmony/Renderer/Buffer.h"

namespace Harmony
{

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual const BufferLayout& get_layout() const override { return _layout; }
		virtual void set_layout(const BufferLayout& layout) override { _layout = layout; }
	private:
		uint32_t _renderer_id;
		BufferLayout _layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void bind() const;
		virtual void unbind() const;

		virtual uint32_t get_count() const { return _count; }
	private:
		uint32_t _renderer_id;
		uint32_t _count;
	};

}