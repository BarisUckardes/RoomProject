#pragma once
#include <Engine/Graphics/Shader/ShaderStage.h>

namespace Engine
{
	class ENGINE_API ShaderUtils
	{
	public:
		ShaderUtils() = delete;
		~ShaderUtils() = delete;

		FORCEINLINE static unsigned int get_shader_stage(const ShaderStage stage);
	};


}