#pragma once
#include <Engine/Containers/Array.h>
#include <ForwardRenderer/MeshVertex.h>

namespace Engine
{
	static Array<MeshVertex> get_plane_vertexes()
	{
		Array<MeshVertex> vertexes;
		vertexes.add(MeshVertex({ 1,0,-1 }, {0,1.0f,0}, {0, 0}));
		vertexes.add(MeshVertex({ -1,0,-1 },{0,1.0f,0}, { 1,0 }));
		vertexes.add(MeshVertex({ -1,0,1 },{0,1.0f,0}, { 1,1 }));
		vertexes.add(MeshVertex({ 1,0,1 },{0,1.0f,0}, { 0,1 }));
		return vertexes;
	}
	static Array<unsigned int> get_plane_indexes()
	{
		Array<unsigned int> indexes;
		indexes.add(0);
		indexes.add(1);
		indexes.add(2);

		indexes.add(0);
		indexes.add(2);
		indexes.add(3);

		return indexes;
	}
}