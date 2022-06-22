#include "MeshLoader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <Engine/Message/Message.h>

namespace Engine
{
	void MeshLoader::load_mesh_from_path(const String& path, MeshLoadResult& resultOut)
	{
		MESSAGE("MeshLoader", "Loading from path %s", *path);

		/*
		* Create assimp importer
		*/
		Assimp::Importer importer;

		/*
		* Load file into assimp scene
		*/
		const aiScene* scene = importer.ReadFile(*path, aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

		/*
		* Validate
		*/
		ASSERT(scene != nullptr, "MeshLoader", "Couldnt find the mesh path");
		ASSERT(scene->mNumMeshes != 0, "MeshLoader", "Loaded file has no meshes in it");

		/*
		* Get loaded meshe
		* For our application we will only be looking for the index 0 mesh
		*/
		aiMesh* mesh = scene->mMeshes[0];
		
		/*
		* Validate mesh
		*/
		ASSERT(mesh->HasFaces() && mesh->HasPositions() && mesh->HasNormals(), "MeshLoader", "Specified mesh does not satisfy the input components");

		/*
		* Get mesh diagnostics
		*/
		const unsigned int vertexCount = mesh->mNumVertices;
		const unsigned int indexCount = mesh->mNumFaces;

		for (unsigned int i = 0; i < vertexCount; i++)
		{
			const aiVector3D position =  mesh->mVertices[i];
			const aiVector3D normal = mesh->mNormals[i];
			const aiVector3D uv = mesh->mTextureCoords[0][i];
			const aiVector3D tangent = mesh->mTangents[i];
			const aiVector3D biTangent = mesh->mBitangents[i];

			resultOut.Vertexes.add(
				MeshVertex(
					{position.x,position.y,position.z},
					{ normal.x ,normal.y ,normal.z },
					{tangent.x,tangent.y,tangent.z},
					{biTangent.x,biTangent.y,biTangent.z},
					{uv.x,uv.y})
			);
		}
		for (unsigned int i = 0; i < indexCount; i++)
		{
			const aiFace face = mesh->mFaces[i];

			for (unsigned int p = 0;p < face.mNumIndices;p++)
			{
				resultOut.Indexes.add(face.mIndices[p]);
			}
		}

		MESSAGE("MeshLoader", "Assimp mesh loaded with %d vertexes and %d indexes", vertexCount, indexCount);
	}
}