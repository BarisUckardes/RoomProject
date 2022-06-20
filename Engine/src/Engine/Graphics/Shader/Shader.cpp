#include "Shader.h"
#include <GLAD/glad.h>
#include <Engine/Message/Message.h>
#include <Engine/Graphics/Shader/ShaderUtils.h>

#define MAX_OPENGL_SHADER_ERROR_LOG_LENGTH 512
namespace Engine
{
	void check_shader_compilation(const unsigned int handle)
	{
		GLint state = 0;
		glGetShaderiv(handle, GL_COMPILE_STATUS, &state);
		if (state == GL_FALSE)
		{
			GLint maxLength = 255;
			glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &maxLength);

			char* errorLog = new char[MAX_OPENGL_SHADER_ERROR_LOG_LENGTH];
			glGetShaderInfoLog(handle, maxLength, &maxLength, errorLog);

			ASSERT(false,"OpenGLShader", "Shader compile failed with logs: %s", errorLog);
			delete[] errorLog;
		}
	}

	Shader::Shader(const String& source, const ShaderStage stage)
	{
		/*
		* Create new shader
		*/
		ShaderHandle = glCreateShader(ShaderUtils::get_shader_stage(stage));

		/*
		* Set shader source data
		*/
		const GLchar* charSrc = *Source;
		glShaderSource(ShaderHandle, 1, &charSrc, 0);

		/*
		* Compile the shader with the given source data
		*/
		glCompileShader(ShaderHandle);

		/// <summary>
		/// Check the shader compilation
		/// </summary>
		check_shader_compilation(ShaderHandle);

		/*
		* Initialize this object
		*/
		Source = source;
		Stage = stage;
	}
	Shader::~Shader()
	{
		if (ShaderHandle != 0)
		{
			glDeleteShader(ShaderHandle);
		}
	}
	String Shader::get_source() const
	{
		return Source;
	}
	ShaderStage Shader::get_stage() const
	{
		return Stage;
	}
	unsigned int Shader::get_shader_handle() const
	{
		return ShaderHandle;
	}
}