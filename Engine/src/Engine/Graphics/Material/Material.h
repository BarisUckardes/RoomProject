#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Containers/Array.h>
#include <Engine/Containers/String.h>
#include <glm/vec3.hpp>

namespace Engine
{
	template<typename TParameter>
	struct ENGINE_API MaterialParameter
	{
		TParameter Parameter;
		String Name;
	};

	class ShaderProgram;
	class Texture2D;
	class ENGINE_API Material
	{
	public:
		Material(ShaderProgram* program);
		~Material() = default;

		FORCEINLINE const Array<MaterialParameter<Texture2D*>>& get_texture_parameters() const;
		FORCEINLINE const Array<MaterialParameter<float>>& get_float_parameters() const;
		FORCEINLINE const Array<MaterialParameter<glm::vec3>>& get_vec3_parameters() const;

		FORCEINLINE ShaderProgram* get_program() const;

		FORCEINLINE void set_texture_parameter(const String& parameterName, Texture2D* parameter);
		FORCEINLINE void set_float_parameter(const String& parameterName, const float parameter);
		FORCEINLINE void set_vec3_parameter(const String& parameterName, const glm::vec3& parameter);
	private:
		FORCEINLINE int get_paramater_index(const String& name);
	private:
		Array<MaterialParameter<Texture2D*>> Textures;
		Array<MaterialParameter<float>> Floats;
		Array<MaterialParameter<glm::vec3>> Vector3s;
		ShaderProgram* Program;
	};


}