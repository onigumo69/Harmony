#include "OpenGLShader.h"
#include "Harmony/Core/Core.h"
#include "Harmony/Core/Log.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <vector>
#include <fstream>

namespace Harmony
{

	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;

		HM_CORE_ASSERT(false, "Unknown shader type!");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		std::string source = read_file(filepath);
		auto shader_sources = pre_process(source);
		compile(shader_sources);

		// Extract name from filepath
		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.rfind('.');
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		_name = filepath.substr(lastSlash, count);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertex_source, const std::string& fragment_source)
	{
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertex_source;
		sources[GL_FRAGMENT_SHADER] = fragment_source;
		compile(sources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(_renderer_id);
	}

	std::string OpenGLShader::read_file(const std::string& filepath)
	{
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			HM_CORE_ERROR("Could not open file '{0}'", filepath);
		}
		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::pre_process(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shader_sources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			HM_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			HM_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shader_sources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}
		return shader_sources;
	}

	void OpenGLShader::compile(const std::unordered_map<GLenum, std::string>& shader_sources)
	{
		GLuint program = glCreateProgram();
		HM_CORE_ASSERT(shader_sources.size() <= 2, "We only support 2 shaders for now");
		std::array<GLenum, 2> glShaderIDs;
		int glShaderIDIndex = 0;
		for (auto& kv : shader_sources)
		{
			GLenum type = kv.first;
			const std::string& source = kv.second;

			GLuint shader = glCreateShader(type);
			const GLchar* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
				glDeleteShader(shader);
				HM_CORE_ERROR("{0}", infoLog.data());
				HM_CORE_ASSERT(false, "Shader compilation failure!");
				break;
			}
			glAttachShader(program, shader);
			glShaderIDs[glShaderIDIndex++] = shader;
		}
		_renderer_id = program;

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);

			for (auto id : glShaderIDs)
				glDeleteShader(id);

			HM_CORE_ERROR("{0}", infoLog.data());
			HM_CORE_ASSERT(false, "Shader link failure!");
			return;
		}
		for (auto id : glShaderIDs)
			glDetachShader(program, id);
	}



	void OpenGLShader::bind() const
	{
		glUseProgram(_renderer_id);
	}

	void OpenGLShader::unbind() const
	{
		glUseProgram(0);
	}



	void OpenGLShader::upload_uniform_int(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(_renderer_id, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::upload_uniform_float(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(_renderer_id, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::upload_uniform_float2(const std::string& name, const glm::vec2& value)
	{
		GLint location = glGetUniformLocation(_renderer_id, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::upload_uniform_float3(const std::string& name, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(_renderer_id, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::upload_uniform_float4(const std::string& name, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation(_renderer_id, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::upload_uniform_mat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(_renderer_id, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::upload_uniform_mat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(_renderer_id, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

}