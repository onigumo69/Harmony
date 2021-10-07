#pragma once

#include <string>

namespace Harmony
{

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		static Shader* create(const std::string& vertex_source, const std::string& fragment_source);
	};

}