#pragma once

#include "Harmony/Renderer/VertexArray.h"

namespace Harmony
{

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void add_vertex_buffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void set_index_buffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& get_vertex_buffer() const { return _vertex_buffer; }
		virtual const std::shared_ptr<IndexBuffer>& get_index_buffer() const { return _index_buffer; };
	private:
		uint32_t _renderer_id;
		std::vector<std::shared_ptr<VertexBuffer>> _vertex_buffer;
		std::shared_ptr<IndexBuffer> _index_buffer;
	};
}