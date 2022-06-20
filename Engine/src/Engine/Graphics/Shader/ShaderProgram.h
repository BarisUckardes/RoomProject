#pragma once
#include <Engine/Graphics/Shader/Shader.h>
#include <Engine/Containers/Array.h>

namespace Engine
{
	class ENGINE_API ShaderProgram
	{
	public:
		ShaderProgram(const Array<Shader*>& shaders);
		~ShaderProgram();

		FORCEINLINE unsigned int get_program_handle() const;

		void set_float_parameter(const float value);
		
	private:
		Array<Shader*> Shaders;
		unsigned int ProgramHandle;
	};


}