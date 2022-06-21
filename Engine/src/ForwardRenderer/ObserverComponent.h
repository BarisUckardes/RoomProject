#pragma once
#include <Engine/World/Component.h>
#include <glm/mat4x4.hpp>
namespace Engine
{
	class ENGINE_API ObserverComponent : public Component
	{
		GENERATE_COMPONENT(ObserverComponent)
	public:
		ObserverComponent(const float nearClip = 0.0001f, const float farClip = 1000.0f, const float fieldOfView = 80.0f);
		~ObserverComponent() = default;

		FORCEINLINE glm::mat4x4 get_projection_matrix() const;
		FORCEINLINE glm::mat4x4 get_view_matrix() const;

		virtual void initialize() override;
		virtual void finalize() override;
	private:
		float NearClip;
		float FarClip;
		float FieldOfView;

	};


}