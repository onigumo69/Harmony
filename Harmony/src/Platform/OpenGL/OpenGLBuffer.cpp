#include "OpenGLBuffer.h"

#include "Harmony/Debug/Instrumentor.h"

#include <glad/glad.h>

namespace Harmony
{

	/////////////////////////////////////////////////////////////////////////////
	// VertexBuffer /////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
	{
		HM_PROFILE_FUNCTION();

		glCreateBuffers(1, &_renderer_id);
		glBindBuffer(GL_ARRAY_BUFFER, _renderer_id);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		HM_PROFILE_FUNCTION();

		glCreateBuffers(1, &_renderer_id);
		glBindBuffer(GL_ARRAY_BUFFER, _renderer_id);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		HM_PROFILE_FUNCTION();

		glDeleteBuffers(1, &_renderer_id);
	}

	void OpenGLVertexBuffer::bind() const
	{
		HM_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, _renderer_id);
	}

	void OpenGLVertexBuffer::unbind() const
	{
		HM_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::set_data(const void* data, uint32_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, _renderer_id);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	/////////////////////////////////////////////////////////////////////////////
	// IndexBuffer //////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		: _count(count)
	{
		HM_PROFILE_FUNCTION();

		glCreateBuffers(1, &_renderer_id);

		// GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
		// Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state
		glBindBuffer(GL_ARRAY_BUFFER, _renderer_id);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		HM_PROFILE_FUNCTION();

		glDeleteBuffers(1, &_renderer_id);
	}

	void OpenGLIndexBuffer::bind() const
	{
		HM_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _renderer_id);
	}

	void OpenGLIndexBuffer::unbind() const
	{
		HM_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}