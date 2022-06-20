#pragma once
#include <Engine/Graphics/Mesh/MeshVertexElementDesc.h>

namespace Engine
{
	class ENGINE_API MeshVertexElementUtils
	{
	public:
		MeshVertexElementUtils() = default;
		~MeshVertexElementUtils() = default;

		FORCEINLINE static unsigned int get_data_size(const MeshVertexElementType type);
		FORCEINLINE static unsigned int get_component_size(const MeshVertexElementType type);
	};


}