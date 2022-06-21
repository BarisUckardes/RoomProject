#pragma once
#include <Engine/Core/Symbols.h>
#include <glm/vec2.hpp>

namespace Engine
{
	struct ENGINE_API UIVertex
	{
		UIVertex(const glm::vec2& pos) : Position(pos) {}
		UIVertex() = default;
		~UIVertex() = default;

		glm::vec2 Position;
	};
}