#include "MeshVertexLayout.h"
#include <Engine/Graphics/Mesh/MeshVertexElementUtils.h>

namespace Engine
{
	MeshVertexLayout::MeshVertexLayout(const Array<MeshVertexElementDesc>& elements)
	{
		/*
		* Calculate stride
		*/
		unsigned int stride = 0;
		for (unsigned int i = 0; i < elements.get_cursor(); i++)
		{
			const MeshVertexElementDesc& desc = elements[i];
			stride += MeshVertexElementUtils::get_data_size(desc.Type);
		}

		/*
		* Initialize
		*/
		Elements = elements;
		Stride = stride;
	}
	const Array<MeshVertexElementDesc>& MeshVertexLayout::get_elements() const
	{
		return Elements;
	}
	unsigned int MeshVertexLayout::get_stride() const
	{
		return Stride;
	}
}