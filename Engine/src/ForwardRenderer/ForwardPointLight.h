#pragma once
#include <Engine/World/Component.h>
#include <glm/vec3.hpp>
namespace Engine
{
	class ENGINE_API ForwardPointLight final : public Component
	{
		GENERATE_COMPONENT(ForwardPointLight)
	public:
		ForwardPointLight(const glm::vec3& color = { 1.0f,0,0 }, const float range = 10.0f);
		~ForwardPointLight() = default;

		FORCEINLINE glm::vec3 get_color() const;
		FORCEINLINE float get_range() const;

		FORCEINLINE void set_color(const glm::vec3& color);
		FORCEINLINE void set_range(const float range);

		// Inherited via Component
		virtual void initialize() override;
		virtual void finalize() override;
	private:
		glm::vec3 Color;
		float Range;

	
	};


}