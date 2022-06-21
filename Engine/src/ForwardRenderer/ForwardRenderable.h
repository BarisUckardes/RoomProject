#pragma once
#include <Engine/World/Component.h>

namespace Engine
{
	class Mesh;
	class ShaderProgram;
	class Material;
	class ENGINE_API ForwardRenderable : public Component
	{
		GENERATE_COMPONENT(ForwardRenderable)
	public:
		ForwardRenderable();
		~ForwardRenderable();

		FORCEINLINE void set_static_mesh(Mesh* staticMesh);
		FORCEINLINE void set_material(Material* material);

		FORCEINLINE Mesh* get_static_mesh() const;
		FORCEINLINE Material* get_material() const;

		// Inherited via Component
		virtual void initialize() override;
		virtual void finalize() override;
	private:
		Mesh* StaticMesh;
		Material* TargetMaterial;

	};


}