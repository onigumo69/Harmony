#pragma once

#include "Buffer.h"

#include <memory>

namespace Harmony
{

	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void add_vertex_buffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void set_index_buffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& get_vertex_buffer() const = 0;
		virtual const Ref<IndexBuffer>& get_index_buffer() const = 0;

		static Ref<VertexArray> create();
	};

}