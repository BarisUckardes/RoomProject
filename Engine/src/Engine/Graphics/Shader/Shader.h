#pragma once
#include <Engine/Containers/String.h>
#include <Engine/Graphics/Shader/ShaderStage.h>
namespace Engine
{
	/// <summary>
	/// Represents a single compiled shader
	/// </summary>
	class ENGINE_API Shader
	{
	public:
		Shader(const String& source,const ShaderStage stage);
		~Shader();

		FORCEINLINE String get_source() const;
		FORCEINLINE ShaderStage get_stage() const;
		FORCEINLINE unsigned int get_shader_handle() const;
	private:
		String Source;
		ShaderStage Stage;
		unsigned int ShaderHandle;
	};


}