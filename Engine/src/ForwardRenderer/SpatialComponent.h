#pragma once
#include <Engine/World/Component.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
namespace Engine
{
	class ENGINE_API SpatialComponent : public Component
	{
		GENERATE_COMPONENT(SpatialComponent)
	public:
		SpatialComponent(const glm::vec3& position = {0,0,0}, const glm::vec3& rotation = {0,0,0}, const glm::vec3& scale = {1,1,1});
		~SpatialComponent() = default;

		FORCEINLINE glm::vec3 get_position() const;
		FORCEINLINE glm::vec3 get_rotation() const;
		FORCEINLINE glm::vec3 get_scale() const;
		FORCEINLINE glm::vec3 get_forward_vector() const;
		FORCEINLINE glm::vec3 get_right_vector() const;
		FORCEINLINE glm::mat4x4 get_model_matrix() const;

		FORCEINLINE void set_position(const glm::vec3& position);
		FORCEINLINE void set_rotation(const glm::vec3& rotation);
		FORCEINLINE void set_scale(const glm::vec3& scale);

		virtual void initialize() override;
		virtual void finalize() override;
	private:
		glm::vec3 Position;
		glm::vec3 Rotation;
		glm::vec3 Scale;
	};


}