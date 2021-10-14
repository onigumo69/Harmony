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

		virtual void add_vertex_buffer(const Ref<VertexBuffer>& vertex_buffer) override;
		virtual void set_index_buffer(const Ref<IndexBuffer>& index_buffer) override;

		virtual const std::vector<Ref<VertexBuffer>>& get_vertex_buffer() const { return _vertex_buffer; }
		virtual const Ref<IndexBuffer>& get_index_buffer() const { return _index_buffer; };
	private:
		uint32_t _renderer_id;
		std::vector<Ref<VertexBuffer>> _vertex_buffer;
		Ref<IndexBuffer> _index_buffer;
	};
}