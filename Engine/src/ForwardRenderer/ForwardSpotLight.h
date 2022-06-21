#pragma once
#include <Engine/World/Component.h>
#include <glm/vec3.hpp>

namespace Engine
{
	class ENGINE_API ForwardSpotLight : public Component
	{
		GENERATE_COMPONENT(ForwardSpotLight)
	public:
		ForwardSpotLight(const glm::vec3& color = {0.8f,0.08f,0.08f}, const float radius = 80.0f, const float range = 35.0f);
		~ForwardSpotLight() = default;

		FORCEINLINE glm::vec3 get_color() const;
		FORCEINLINE float get_radius() const;
		FORCEINLINE float get_range() const;

		FORCEINLINE void set_color(const glm::vec3& color);
		FORCEINLINE void set_radius(const float radius);
		FORCEINLINE void set_range(const float range);

		// Inherited via Component
		virtual void initialize() override;
		virtual void finalize() override;
	private:
		glm::vec3 Color;
		float Radius;
		float Range;

		
	};


}