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

		virtual void add_vertex_buffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual void set_index_buffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& get_vertex_buffer() const = 0;
		virtual const std::shared_ptr<IndexBuffer>& get_index_buffer() const = 0;

		static VertexArray* create();
	};

}