#include "Harmony/Core/Core.h"
#include "Harmony/Core/Log.h"
#include "Harmony/Debug/Instrumentor.h"

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
		HM_PROFILE_FUNCTION();

		glCreateVertexArrays(1, &_renderer_id);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		HM_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &_renderer_id);
	}

	void OpenGLVertexArray::bind() const
	{
		HM_PROFILE_FUNCTION();

		glBindVertexArray(_renderer_id);
	}

	void OpenGLVertexArray::unbind() const
	{
		HM_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	void OpenGLVertexArray::add_vertex_buffer(const Ref<VertexBuffer>& vertex_buffer)
	{
		HM_PROFILE_FUNCTION();

		HM_CORE_ASSERT(vertex_buffer->get_layout().get_elements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(_renderer_id);
		vertex_buffer->bind();

		const auto& layout = vertex_buffer->get_layout();
		for (const auto& element : layout)
		{
			switch (element._type)
			{
			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
			case ShaderDataType::Int:
			case ShaderDataType::Int2:
			case ShaderDataType::Int3:
			case ShaderDataType::Int4:
			case ShaderDataType::Bool:
			{
				glEnableVertexAttribArray(_vertex_buffer_index);
				glVertexAttribPointer(_vertex_buffer_index,
					element.get_component_count(),
					ShaderDataTypeToOpenGLBaseType(element._type),
					element._normalized ? GL_TRUE : GL_FALSE,
					layout.get_stride(),
					(const void*)element._offset);
				_vertex_buffer_index++;
				break;
			}
			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4:
			{
				uint8_t count = element.get_component_count();
				for (uint8_t i = 0; i < count; i++)
				{
					glEnableVertexAttribArray(_vertex_buffer_index);
					glVertexAttribPointer(_vertex_buffer_index,
						count,
						ShaderDataTypeToOpenGLBaseType(element._type),
						element._normalized ? GL_TRUE : GL_FALSE,
						layout.get_stride(),
						(const void*)(element._offset + sizeof(float) * count * i));

					glVertexAttribDivisor(_vertex_buffer_index, 1);
					_vertex_buffer_index++;
				}
				break;
			}
			default:
				HM_CORE_ASSERT(false, "Unknown ShaderDataType!");
			}
		}

		_vertex_buffer.push_back(vertex_buffer);
	}

	void OpenGLVertexArray::set_index_buffer(const Ref<IndexBuffer>& index_buffer)
	{
		HM_PROFILE_FUNCTION();

		glBindVertexArray(_renderer_id);
		index_buffer->bind();

		_index_buffer = index_buffer;
	}

}