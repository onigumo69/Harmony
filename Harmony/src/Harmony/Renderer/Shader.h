#pragma once

#include "Harmony/Core/Core.h"

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

namespace Harmony
{

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void set_int(const std::string& name, int value) = 0;
		virtual void set_int_array(const std::string& name, int* values, uint32_t count) = 0;
		virtual void set_float(const std::string& name, float value) = 0;
		virtual void set_float3(const std::string& name, const glm::vec3& value) = 0;
		virtual void set_float4(const std::string& name, const glm::vec4& value) = 0;
		virtual void set_mat4(const std::string& name, const glm::mat4& value) = 0;

		virtual const std::string& get_name() const = 0;

		static Ref<Shader> create(const std::string& filepath);
		static Ref<Shader> create(const std::string& name, const std::string& vertex_source, const std::string& fragment_source);
	};

	class ShaderLibrary
	{
	public:
		void add(const std::string& name, const Ref<Shader>& shader);
		void add(const Ref<Shader>& shader);
		Ref<Shader> load(const std::string& filepath);
		Ref<Shader> load(const std::string& name, const std::string& filepath);

		Ref<Shader> get(const std::string& name);

		bool exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> _shaders;
	};
}