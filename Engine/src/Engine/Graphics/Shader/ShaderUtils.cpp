#include "ShaderUtils.h"
#include <GLAD/glad.h>

namespace Engine
{
	unsigned int ShaderUtils::get_shader_stage( ShaderStage stage)
	{
		switch (stage)
		{
			case Engine::ShaderStage::Vertex:
				return GL_VERTEX_SHADER;
			case Engine::ShaderStage::Fragment:
				return GL_FRAGMENT_SHADER;
			default:
				break;
		}
	}
}