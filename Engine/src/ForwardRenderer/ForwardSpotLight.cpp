#include "ForwardSpotLight.h"
#include <Engine/World/World.h>
#include <Engine/World/Entity.h>
#include <ForwardRenderer/ForwardRendererFunction.h>

namespace Engine
{
	ForwardSpotLight::ForwardSpotLight(const glm::vec3& color, const float radius, const float range)
	{
		Color = color;
		Radius = radius;
		Range = range;
	}
	glm::vec3 ForwardSpotLight::get_color() const
	{
		return Color;
	}
	float ForwardSpotLight::get_radius() const
	{
		return Radius;
	}
	float ForwardSpotLight::get_range() const
	{
		return Range;
	}
	void ForwardSpotLight::set_color(const glm::vec3& color)
	{
		Color = color;
	}
	void ForwardSpotLight::set_radius(const float radius)
	{
		Radius = radius;
	}
	void ForwardSpotLight::set_range(const float range)
	{
		Range = range;
	}
	void ForwardSpotLight::initialize()
	{
		get_owner_entity()->get_owner_world()->get_function<ForwardRendererFunction>()->register_spot_light(this);
	}
	void ForwardSpotLight::finalize()
	{
		get_owner_entity()->get_owner_world()->get_function<ForwardRendererFunction>()->remove_spot_light(this);
	}
}