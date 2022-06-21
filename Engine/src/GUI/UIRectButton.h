#pragma once
#include <Engine/World/Component.h>
#include <glm/vec3.hpp>

namespace Engine
{
	class Material;
	class Mesh;
	class ENGINE_API UIRectButton : public Component
	{
		GENERATE_COMPONENT(UIRectButton)
	public:
		UIRectButton() : Mat(nullptr),StaticMesh(nullptr),Color({1.0f,0,0}),Width(0),Height(0) {}
		~UIRectButton() = default;

		FORCEINLINE glm::vec3 get_color() const;
		FORCEINLINE float get_width() const;
		FORCEINLINE float get_height() const;

		FORCEINLINE Material* get_material() const;
		FORCEINLINE Mesh* get_mesh() const;

		FORCEINLINE void set_color(const glm::vec3& color);

		FORCEINLINE void set_material(Material* material);
		FORCEINLINE void set_mesh(Mesh* mesh);

		FORCEINLINE virtual void on_button_click() = 0;

		virtual void initialize() override;
		virtual void finalize() override;
	private:
		Material* Mat;
		Mesh* StaticMesh;
		glm::vec3 Color;
		float Width;
		float Height;
	};


}