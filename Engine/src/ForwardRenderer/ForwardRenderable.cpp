#include "ForwardRenderable.h"
#include <ForwardRenderer/ForwardRendererFunction.h>
#include <Engine/World/World.h>
#include <Engine/World/Entity.h>

namespace Engine
{
	ForwardRenderable::ForwardRenderable()
	{
		StaticMesh = nullptr;
		TargetMaterial = nullptr;
	}
	ForwardRenderable::~ForwardRenderable()
	{

	}
	void ForwardRenderable::set_static_mesh(Mesh* staticMesh)
	{
		StaticMesh = staticMesh;
	}
	void ForwardRenderable::set_material(Material* material)
	{
		TargetMaterial = material;
	}
	Mesh* ForwardRenderable::get_static_mesh() const
	{
		return StaticMesh;
	}
	Material* ForwardRenderable::get_material() const
	{
		return TargetMaterial;
	}
	void ForwardRenderable::initialize()
	{
		get_owner_entity()->get_owner_world()->get_function<ForwardRendererFunction>()->register_renderable(this);
	}
	void ForwardRenderable::finalize()
	{
		get_owner_entity()->get_owner_world()->get_function<ForwardRendererFunction>()->remove_renderable(this);
	}
}