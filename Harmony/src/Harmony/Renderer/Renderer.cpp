#include "Renderer.h"
#include "RenderCommand.h"

namespace Harmony
{

	void Renderer::begin_scene()
	{
	}

	void Renderer::end_scene()
	{
	}

	void Renderer::submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->bind();
		RenderCommand::draw_indexed(vertexArray);
	}

}