#include "SpatialComponent.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{
	SpatialComponent::SpatialComponent(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
	{
		Position = position;
		Rotation = rotation;
		Scale = scale;
	}
	glm::vec3 SpatialComponent::get_position() const
	{
		return Position;
	}
	glm::vec3 SpatialComponent::get_rotation() const
	{
		return Rotation;
	}
	glm::vec3 SpatialComponent::get_scale() const
	{
		return Scale;
	}
	glm::vec3 SpatialComponent::get_forward_vector() const
	{
		glm::mat4x4 rot = glm::mat4x4(1.0f);
		rot = glm::rotate(rot, glm::radians(Rotation.x), glm::vec3(1.0f, 0, 0));
		rot = glm::rotate(rot, glm::radians(Rotation.y), glm::vec3(0, 1.0f, 0));
		rot = glm::rotate(rot, glm::radians(Rotation.z), glm::vec3(0, 0, 1.0f));
		glm::vec4 v4 = glm::vec4(0, 0, 1, 0) * rot;
		return glm::vec3(v4.x, v4.y, v4.z);
	}
	glm::vec3 SpatialComponent::get_right_vector() const
	{
		const glm::vec3 forwardVector = get_forward_vector();
		return glm::cross(glm::vec3(0, 1, 0), forwardVector);
	}
	glm::mat4x4 SpatialComponent::get_model_matrix() const
	{
		glm::mat4x4 model(1.0f);
		model = glm::translate(model, Position);
		model = glm::scale(model, Scale);
		model = glm::rotate(model, glm::radians(Rotation.x), glm::vec3(1.0f, 0, 0));
		model = glm::rotate(model, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0));
		model = glm::rotate(model, glm::radians(Rotation.z), glm::vec3(0.0f, 0, 1.0f));
		return model;
	}
	void SpatialComponent::set_position(const glm::vec3& position)
	{
		Position = position;
	}
	void SpatialComponent::set_rotation(const glm::vec3& rotation)
	{
		Rotation = rotation;
	}
	void SpatialComponent::set_scale(const glm::vec3& scale)
	{
		Scale = scale;
	}
	void SpatialComponent::initialize()
	{

	}
	void SpatialComponent::finalize()
	{

	}
}