#pragma once
#include <Engine/Core/Symbols.h>

namespace Engine
{
	/// <summary>
	/// Supported vertex element types
	/// </summary>
	enum class ENGINE_API MeshVertexElementType
	{
		Float,
		Float2,
		Float3,
		Float4,
		Mat3x3,
		Mat4x4
	};
}