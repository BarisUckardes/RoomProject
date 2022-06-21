#include "ForwardPointLight.h"
#include <Engine/World/Entity.h>
#include <Engine/World/World.h>
#include <ForwardRenderer/ForwardRendererFunction.h>
namespace Engine
{
	ForwardPointLight::ForwardPointLight(const glm::vec3& color, const float range)
	{
		Color = color;
		Range = range;
	}
	glm::vec3 ForwardPointLight::get_color() const
	{
		return Color;
	}
	float ForwardPointLight::get_range() const
	{
		return Range;
	}
	void ForwardPointLight::set_color(const glm::vec3& color)
	{
		Color = color;
	}
	void ForwardPointLight::set_range(const float range)
	{
		Range = range;
	}

	void ForwardPointLight::initialize()
	{
		get_owner_entity()->get_owner_world()->get_function<ForwardRendererFunction>()->register_point_light(this);
	}
	void ForwardPointLight::finalize()
	{
		get_owner_entity()->get_owner_world()->get_function<ForwardRendererFunction>()->remove_point_light(this);
	}
}