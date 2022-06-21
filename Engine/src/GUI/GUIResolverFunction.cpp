#include "GUIResolverFunction.h"
#include <GUI/UIRectButton.h>
#include <GLAD/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <Engine/Window/Window.h>
#include <Engine/Graphics/Material/Material.h>
#include <Engine/Graphics/Mesh/Mesh.h>
#include <Engine/Graphics/Shader/ShaderProgram.h>
#include <Engine/Message/Message.h>
#include <Engine/World/Entity.h>
#include <ForwardRenderer/SpatialComponent.h>
#include <Engine/Input/GameInput.h>

#define ORTHO 1.0f
namespace Engine
{
    void GUIResolverFunction::register_button(UIRectButton* rect)
    {
        Buttons.add(rect);
    }
    void GUIResolverFunction::remove_button(UIRectButton* rect)
    {
        Buttons.remove(rect);
    }
    void GUIResolverFunction::initialize()
    {

    }
    void GUIResolverFunction::execute()
    {
        glDisable(GL_DEPTH_TEST);

        /*
        * calculate aspect ratio of uniform boxes
        */
        const float aspectRatio = Window::get_window_width() / Window::get_window_height();

        /*
        * calculate the ortho matrix
        */
        glm::mat4x4 orthoMatrix = glm::ortho(-ORTHO, ORTHO, ORTHO, -ORTHO,-1000.0f, 1000.0f);

        /*
        * Render each button using ortho projection
        */
        for (unsigned int i = 0;i < Buttons.get_cursor(); i++)
        {
            const UIRectButton* button = Buttons[i];
            const Material* material = button->get_material();
            const Mesh* mesh = button->get_mesh();
            const unsigned int programHandle = material->get_program()->get_program_handle();
            const glm::vec3 color = button->get_color();
            const glm::vec3 pos = button->get_owner_entity()->get_component<SpatialComponent>()->get_position();

            glBindVertexArray(mesh->get_vertex_array_handle());
            glBindBuffer(GL_ARRAY_BUFFER, mesh->get_vertex_buffer_handle());
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->get_index_buffer_handle());

            glUseProgram(programHandle);

            glUniform3f(glGetUniformLocation(programHandle, "f_Color"), color.x, color.y, color.z);
            glUniform2f(glGetUniformLocation(programHandle,"v_Position"),pos.x* ORTHO,pos.y*ORTHO);
            glUniformMatrix4fv(glGetUniformLocation(programHandle, "v_Ortho"),
                1,
                GL_FALSE,
                &orthoMatrix[0][0]);

            glDrawElements(GL_TRIANGLES, mesh->get_index_buffer_element_count(), GL_UNSIGNED_INT, nullptr);
        }

        /*
        * Check which buttons have been clicked
        */
        const float screenSpaceMousePosX = ((GameInput::get_mouse_pos_x() / Window::get_window_width()) -0.5f)*2.0f;
        const float screenSpaceMousePosY = (GameInput::get_mouse_pos_y() / Window::get_window_height());
        constexpr float ratio = 1.0f / 10.0f;
        for (unsigned int i = 0; i < Buttons.get_cursor(); i++)
        {
            UIRectButton* button = Buttons[i];
            glm::vec3 pos = button->get_owner_entity()->get_component<SpatialComponent>()->get_position();

            /*
            * Validate box
            */
            if (screenSpaceMousePosX + ratio >= pos.x && screenSpaceMousePosX <= pos.x + ratio && screenSpaceMousePosY + ratio >= pos.y && screenSpaceMousePosY <= pos.y + ratio)
            {
                if(GameInput::is_button_pressed(1))
                    button->on_button_click();
            }
        }

    }
    void GUIResolverFunction::finalize()
    {

    }
}