#include "Renderer.h"
#include "RenderCommand.h"

namespace Harmony
{
	Renderer::SceneData* Renderer::_scene_data = new Renderer::SceneData;

	void Renderer::begin_scene(OrthographicCamera& camera)
	{
		_scene_data->_view_projection_matrix = camera.get_view_projection_matrix();
	}

	void Renderer::end_scene()
	{
	}

	void Renderer::submit(const std::shared_ptr<Shader>& shader,
		const std::shared_ptr<VertexArray>& vertex_array,
		const glm::mat4& transform)
	{
		shader->bind();
		shader->upload_uniform_mat4("u_ViewProjection", _scene_data->_view_projection_matrix);
		shader->upload_uniform_mat4("u_Transform", transform);

		vertex_array->bind();
		RenderCommand::draw_indexed(vertex_array);
	}

}