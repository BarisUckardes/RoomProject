#pragma once
#include <Engine/Core/Symbols.h>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float2.hpp>

namespace Engine
{
	struct ENGINE_API MeshVertex
	{
		MeshVertex(const glm::vec3& pos,const glm::vec3& normal, const glm::vec2& uv) : Position(pos),Normal(normal), TextureCoordinate(uv) {}
		MeshVertex() = default;
		~MeshVertex() = default;
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TextureCoordinate;
	};
}