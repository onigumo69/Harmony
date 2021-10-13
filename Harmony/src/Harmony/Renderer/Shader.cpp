#include "Shader.h"

#include "Harmony/Core/Core.h"
#include "Harmony/Core/Log.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <vector>

namespace Harmony
{

	Ref<Shader> Shader::create(const std::string& filepath)
	{
		switch (Renderer::get_api())
		{
		case RendererAPI::API::None:    HM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return create_ref<OpenGLShader>(filepath);
		}

		HM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Shader> Shader::create(const std::string& name, const std::string& vertex_source, const std::string& fragment_source)
	{
		switch (Renderer::get_api())
		{
		case RendererAPI::API::None:    HM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return create_ref<OpenGLShader>(name, vertex_source, fragment_source);
		}

		HM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	void ShaderLibrary::add(const std::string& name, const Ref<Shader>& shader)
	{
		HM_CORE_ASSERT(!exists(name), "Shader already exists!");
		_shaders[name] = shader;
	}

	void ShaderLibrary::add(const Ref<Shader>& shader)
	{
		auto& name = shader->get_name();
		add(name, shader);
	}

	Ref<Shader> ShaderLibrary::load(const std::string& filepath)
	{
		auto shader = Shader::create(filepath);
		add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::create(filepath);
		add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::get(const std::string& name)
	{
		HM_CORE_ASSERT(exists(name), "Shader not found!");
		return _shaders[name];
	}

	bool ShaderLibrary::exists(const std::string& name) const
	{
		return _shaders.find(name) != _shaders.end();
	}
}