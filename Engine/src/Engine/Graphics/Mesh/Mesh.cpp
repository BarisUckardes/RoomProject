#include "Mesh.h"
#include <GLAD/glad.h>
#include <Engine/Graphics/Mesh/MeshVertexElementUtils.h>
#include <Engine/Message/Message.h>

namespace Engine
{
	Mesh::Mesh(const MeshVertexLayout& layout)
	{
		/*
		* Generate vertex buffer,index buffer and vertex arrays
		*/
		glGenBuffers(1, &VertexBufferHandle);
		glGenBuffers(1, &IndexBufferHandle);
		glGenVertexArrays(1, &VertexArrayHandle);

		glBindVertexArray(VertexArrayHandle);
		glBindBuffer(GL_ARRAY_BUFFER, VertexBufferHandle);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferHandle);

		/*
		* Set vertex array attributes
		*/
		const Array<MeshVertexElementDesc>& elements = layout.get_elements();
		const unsigned int stride = layout.get_stride();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < elements.get_cursor(); i++)
		{
			const MeshVertexElementDesc& element = elements[i];

			glEnableVertexAttribArray(i);

			glVertexAttribPointer(i, MeshVertexElementUtils::get_component_size(element.Type), GL_FLOAT, element.Normalized, stride, (const void*)(offset));

			offset += MeshVertexElementUtils::get_data_size(element.Type);
			
		}

	
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		/*
		* Initialize
		*/
		Layout = layout;
		VertexBufferSize = 0;
		IndexBufferSize = 0;
		IndexBufferElementCount = 0;
		
	}
	Mesh::~Mesh()
	{
		if (VertexArrayHandle != 0)
		{
			glDeleteVertexArrays(1,&VertexArrayHandle);
			glDeleteBuffers(1, &VertexBufferHandle);
			glDeleteBuffers(1, &IndexBufferHandle);
			IndexBufferSize = 0;
			IndexBufferElementCount = 0;
			VertexBufferSize = 0;
		}
	}
	unsigned int Mesh::get_vertex_buffer_handle() const
	{
		return VertexBufferHandle;
	}
	unsigned long Mesh::get_vertex_buffer_size() const
	{
		return VertexBufferSize;
	}
	unsigned int Mesh::get_index_buffer_handle() const
	{
		return IndexBufferHandle;
	}
	unsigned long Mesh::get_index_buffer_size() const
	{
		return IndexBufferSize;
	}
	unsigned long Mesh::get_index_buffer_element_count() const
	{
		return IndexBufferElementCount;
	}
	unsigned int Mesh::get_vertex_array_handle() const
	{
		return VertexArrayHandle;
	}
	void Mesh::allocate_vertex_data(const unsigned long size)
	{
		/*
		* Allocate vertex data
		*/
		glBindBuffer(GL_ARRAY_BUFFER, VertexBufferHandle);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		VertexBufferSize = size;
	}
	void Mesh::allocate_index_data(const unsigned long size, const unsigned long indexBufferElementCount)
	{
		/*
		* Allocate index data
		*/
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferHandle);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		IndexBufferSize = size;
		IndexBufferElementCount = indexBufferElementCount;
	}
	void Mesh::update_vertex_data(const void* dataPtr)
	{
		/*
		* Update vertex data
		*/
		glBindBuffer(GL_ARRAY_BUFFER, VertexBufferHandle);
		glBufferSubData(GL_ARRAY_BUFFER, 0, VertexBufferSize, dataPtr);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void Mesh::update_index_data(const void* dataPtr)
	{
		/*
		* Update index data
		*/
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferHandle);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, IndexBufferSize, dataPtr);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}