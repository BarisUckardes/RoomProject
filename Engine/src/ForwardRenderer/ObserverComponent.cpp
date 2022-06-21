#include "ObserverComponent.h"
#include <glm/gtc/matrix_transform.hpp>
#include <ForwardRenderer/SpatialComponent.h>
#include <Engine/World/Entity.h>
#include <Engine/World/World.h>
#include <ForwardRenderer/ForwardRendererFunction.h>
#include <Engine/Window/Window.h>

namespace Engine
{
	ObserverComponent::ObserverComponent(const float nearClip, const float farClip, const float fieldOfView)
	{
		NearClip = nearClip;
		FarClip = farClip;
		FieldOfView = fieldOfView;
	}
	glm::mat4x4 ObserverComponent::get_projection_matrix() const
	{
		const float fovInRadians = glm::radians(FieldOfView); // field of view required in radias
		const float aspectRatio = Window::get_window_width() / (float)Window::get_window_height(); // fixed might cause trouble

		return glm::perspective(fovInRadians, aspectRatio, NearClip, FarClip);
	}
	glm::mat4x4 ObserverComponent::get_view_matrix() const
	{
		const SpatialComponent* spatial = get_owner_entity()->get_component<SpatialComponent>();

		const glm::vec3 position = spatial->get_position();
		const glm::vec3 lookDirection = spatial->get_forward_vector();
		const glm::vec3 lookPosition = position + lookDirection;
		const glm::vec3 relativeUp = glm::vec3(0, 1, 0);

		return glm::lookAt(position, position + lookDirection, relativeUp);
	}
	void ObserverComponent::initialize()
	{
		get_owner_entity()->get_owner_world()->get_function<ForwardRendererFunction>()->set_observer(this);
	}
	void ObserverComponent::finalize()
	{
		get_owner_entity()->get_owner_world()->get_function<ForwardRendererFunction>()->set_observer(nullptr);
	}
}