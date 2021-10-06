#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Harmony
{

	RendererAPI* RenderCommand::_renderer_api = new OpenGLRendererAPI;

}