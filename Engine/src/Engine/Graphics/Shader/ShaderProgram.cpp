#include "ShaderProgram.h"
#include <GLAD/glad.h>
#include <Engine/Message/Message.h>

namespace Engine
{
	void check_program_linkage(const unsigned int handle)
	{
		GLint state = 0;
		glGetProgramiv(handle, GL_LINK_STATUS, (int*)&state);
		if (state == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &maxLength);

			char* errorLog = new char[maxLength];
			glGetProgramInfoLog(handle, maxLength, &maxLength, errorLog);

			ASSERT(false,"OpenGLRenderPass", "Program cannot be linked with these logs: %s", errorLog);

			delete[] errorLog;
		}
	}

	ShaderProgram::ShaderProgram(const Array<Shader*>& shaders)
	{
		/*
		* Create shader program
		*/
		ProgramHandle = glCreateProgram();

		/*
		* Attach the shaders to program
		*/
		for (unsigned int i = 0; i < shaders.get_cursor(); i++)
		{
			const Shader* shader = shaders[i];

			glAttachShader(ProgramHandle, shader->get_shader_handle());
		}

		/*
		* Link program
		*/
		glLinkProgram(ProgramHandle);

		/*
		* Check link result
		*/
		check_program_linkage(ProgramHandle);
	}
	ShaderProgram::~ShaderProgram()
	{
		if (ProgramHandle != 0)
			glDeleteProgram(ProgramHandle);
	}
	unsigned int ShaderProgram::get_program_handle() const
	{
		return ProgramHandle;
	}
}