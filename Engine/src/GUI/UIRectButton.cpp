#include "UIRectButton.h"
#include <Engine/World/Entity.h>
#include <Engine/World/World.h>
#include <GUI/GUIResolverFunction.h>

namespace Engine
{
    glm::vec3 UIRectButton::get_color() const
    {
        return Color;
    }
    float UIRectButton::get_width() const
    {
        return Width;
    }
    float UIRectButton::get_height() const
    {
        return Height;
    }
    Material* UIRectButton::get_material() const
    {
        return Mat;
    }
    Mesh* UIRectButton::get_mesh() const
    {
        return StaticMesh;
    }
    void UIRectButton::set_color(const glm::vec3& color)
    {
        Color = color;
    }
    void UIRectButton::set_material(Material* material)
    {
        Mat = material;
    }
    void UIRectButton::set_mesh(Mesh* mesh)
    {
        StaticMesh = mesh;
    }
    void UIRectButton::initialize()
    {
        get_owner_entity()->get_owner_world()->get_function<GUIResolverFunction>()->register_button(this);
    }
    void UIRectButton::finalize()
    {
        get_owner_entity()->get_owner_world()->get_function<GUIResolverFunction>()->remove_button(this);
    }
}