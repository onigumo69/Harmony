#include "Harmony/Core.h"
#include "Harmony/Log.h"

#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Harmony
{

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Harmony::ShaderDataType::Float:    return GL_FLOAT;
		case Harmony::ShaderDataType::Float2:   return GL_FLOAT;
		case Harmony::ShaderDataType::Float3:   return GL_FLOAT;
		case Harmony::ShaderDataType::Float4:   return GL_FLOAT;
		case Harmony::ShaderDataType::Mat3:     return GL_FLOAT;
		case Harmony::ShaderDataType::Mat4:     return GL_FLOAT;
		case Harmony::ShaderDataType::Int:      return GL_INT;
		case Harmony::ShaderDataType::Int2:     return GL_INT;
		case Harmony::ShaderDataType::Int3:     return GL_INT;
		case Harmony::ShaderDataType::Int4:     return GL_INT;
		case Harmony::ShaderDataType::Bool:     return GL_BOOL;
		}

		HM_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &_renderer_id);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &_renderer_id);
	}

	void OpenGLVertexArray::bind() const
	{
		glBindVertexArray(_renderer_id);
	}

	void OpenGLVertexArray::unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::add_vertex_buffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		HM_CORE_ASSERT(vertexBuffer->get_layout().get_elements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(_renderer_id);
		vertexBuffer->bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->get_layout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.get_component_count(),
				ShaderDataTypeToOpenGLBaseType(element._type),
				element._normalized ? GL_TRUE : GL_FALSE,
				layout.get_stride(),
				(const void*)element._offset);
			index++;
		}

		_vertex_buffer.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::set_index_buffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(_renderer_id);
		indexBuffer->bind();

		_index_buffer = indexBuffer;
	}

}