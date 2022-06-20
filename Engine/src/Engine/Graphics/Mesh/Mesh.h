#pragma once
#include <Engine/Graphics/Mesh/MeshVertexLayout.h>

namespace Engine
{
	/// <summary>
	/// Represents a mesh which holds both vertex and index data along with a vertex array handle
	/// <para>Authors some operations such as allocating and updating vertex and index buffer data</para>
	/// </summary>
	class ENGINE_API Mesh
	{
	public:
		Mesh(const MeshVertexLayout& layout);
		~Mesh();

		FORCEINLINE unsigned int get_vertex_buffer_handle() const;
		FORCEINLINE unsigned long get_vertex_buffer_size() const;
		FORCEINLINE unsigned int get_index_buffer_handle() const;
		FORCEINLINE unsigned long get_index_buffer_size() const;
		FORCEINLINE unsigned long get_index_buffer_element_count() const;
		FORCEINLINE unsigned int get_vertex_array_handle() const;

		void allocate_vertex_data(const unsigned long size);
		void allocate_index_data(const unsigned long size,const unsigned long indexBufferElementCount);

		void update_vertex_data(const void* dataPtr);
		void update_index_data(const void* dataPtr);
	private:
		MeshVertexLayout Layout;
		unsigned long VertexBufferSize;
		unsigned long IndexBufferSize;
		unsigned long IndexBufferElementCount;
		unsigned int VertexBufferHandle;
		unsigned int IndexBufferHandle;
		unsigned int VertexArrayHandle;
	};


}