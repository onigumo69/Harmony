#include "OpenGLShader.h"
#include "Harmony/Core.h"
#include "Harmony/Log.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

#include <vector>

namespace Harmony
{

	OpenGLShader::OpenGLShader(const std::string& vertex_source, const std::string& fragment_source)
	{
		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = vertex_source.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			HM_CORE_ERROR("{0}", infoLog.data());
			HM_CORE_ASSERT(false, "Vertex shader compilation failure!");
			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = fragment_source.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> info_log(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &info_log[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			HM_CORE_ERROR("{0}", info_log.data());
			HM_CORE_ASSERT(false, "Fragment shader compilation failure!");
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		_renderer_id = glCreateProgram();
		GLuint program = _renderer_id;

		// Attach our shaders to our program
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

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
			std::vector<GLchar> info_log(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &info_log[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			HM_CORE_ERROR("{0}", info_log.data());
			HM_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(_renderer_id);
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