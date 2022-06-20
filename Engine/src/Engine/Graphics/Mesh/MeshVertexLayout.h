#pragma once
#include <Engine/Containers/Array.h>
#include <Engine/Graphics/Mesh/MeshVertexElementDesc.h>

namespace Engine
{
	class ENGINE_API MeshVertexLayout
	{
	public:
		MeshVertexLayout(const Array<MeshVertexElementDesc>& elements);
		MeshVertexLayout() = default;
		~MeshVertexLayout() = default;

		FORCEINLINE const Array<MeshVertexElementDesc>& get_elements() const;
		FORCEINLINE unsigned int get_stride() const;
	private:
		Array<MeshVertexElementDesc> Elements;
		unsigned int Stride;
	};


}