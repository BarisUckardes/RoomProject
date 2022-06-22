#pragma once
#include <Engine/Containers/String.h>
#include <Engine/Containers/Array.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <ForwardRenderer/MeshVertex.h>

namespace Engine
{
	struct ENGINE_API MeshLoadResult
	{
		Array<MeshVertex> Vertexes;
		Array<unsigned int> Indexes;
	};

	class ENGINE_API MeshLoader
	{
	public:
		MeshLoader() = delete;
		~MeshLoader() = delete;

		FORCEINLINE static void load_mesh_from_path(const String& path,MeshLoadResult& resultOut);
	};


}