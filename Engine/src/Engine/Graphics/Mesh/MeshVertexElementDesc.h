#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Graphics/Mesh/MeshVertexElementType.h>s
#include <Engine/Containers/String.h>

namespace Engine
{
	/// <summary>
	/// Required fields to form a single vertex element
	/// </summary>
	struct ENGINE_API MeshVertexElementDesc
	{
		MeshVertexElementDesc(const String& name,const MeshVertexElementType type,const bool normalized) : Name(name),Type(type),Normalized(normalized) {}
		MeshVertexElementDesc() = default;
		~MeshVertexElementDesc() = default;

		String Name;
		MeshVertexElementType Type;
		bool Normalized;
	};
}