#pragma once

#include "Harmony/Renderer/Shader.h"
#include <glm/glm.hpp>

#include <unordered_map>

// TODO: REMOVE!
typedef unsigned int GLenum;

namespace Harmony
{

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertex_source, const std::string& fragment_source);
		virtual ~OpenGLShader();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual const std::string& get_name() const override { return _name; }

		void upload_uniform_int(const std::string& name, int value);

		void upload_uniform_float(const std::string& name, float value);
		void upload_uniform_float2(const std::string& name, const glm::vec2& value);
		void upload_uniform_float3(const std::string& name, const glm::vec3& value);
		void upload_uniform_float4(const std::string& name, const glm::vec4& value);

		void upload_uniform_mat3(const std::string& name, const glm::mat3& matrix);
		void upload_uniform_mat4(const std::string& name, const glm::mat4& matrix);
	private:
		std::string read_file(const std::string& filepath);
		std::unordered_map<GLenum, std::string> pre_process(const std::string& source);
		void compile(const std::unordered_map<GLenum, std::string>& shader_sources);
	private:
		uint32_t _renderer_id;
		std::string _name;
	};

}