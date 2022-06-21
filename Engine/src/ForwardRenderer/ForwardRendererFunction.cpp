#include "ForwardRendererFunction.h"
#include <GLAD/glad.h>
#include <Engine/Message/Message.h>
#include <ForwardRenderer/ForwardRenderable.h>
#include <ForwardRenderer/ObserverComponent.h>
#include <ForwardRenderer/SpatialComponent.h>
#include <Engine/Graphics/Shader/ShaderProgram.h>
#include <Engine/Graphics/Mesh/Mesh.h>
#include <Engine/World/Entity.h>
#include <Engine/Graphics/Material/Material.h>
#include <Engine/Graphics/Texture/Texture2D.h>
#include <Engine/World/World.h>
#include <Engine/Application/ApplicationSession.h>
#include <Engine/Window/Window.h>
#include <ForwardRenderer/ForwardPointLight.h>
#include <ForwardRenderer/ForwardSpotLight.h>

#define MAX_POINT_LIGHT_RECEIVE 5
#define MAX_SPOT_LIGHT_RECEIVE 5

namespace Engine
{
    void ForwardRendererFunction::register_renderable(ForwardRenderable* renderable)
    {
        Renderables.add(renderable);
    }
    void ForwardRendererFunction::remove_renderable(ForwardRenderable* renderable)
    {
        Renderables.remove(renderable);
    }
    void ForwardRendererFunction::set_observer(ObserverComponent* observer)
    {
        Observer = observer;
    }
    void ForwardRendererFunction::register_point_light(ForwardPointLight* pointLight)
    {
        PointLights.add(pointLight);
    }
    void ForwardRendererFunction::remove_point_light(ForwardPointLight* pointLight)
    {
        PointLights.add(pointLight);
    }
    void ForwardRendererFunction::register_spot_light(ForwardSpotLight* spotLight)
    {
        SpotLights.add(spotLight);
    }
    void ForwardRendererFunction::remove_spot_light(ForwardSpotLight* spotLight)
    {
        SpotLights.remove(spotLight);
    }
    void ForwardRendererFunction::initialize()
    {
        glEnable(GL_DEPTH_TEST);
    }
    void ForwardRendererFunction::execute()
    {
        /*
        * Set and clear the swapchain framebuffer upfront
        */
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        Window* window = get_owner_world()->get_owner_session()->get_app_window();
        glViewport(0,0,Window::get_window_width(),Window::get_window_height());
        glClearColor(100/255.0f, 149/255.0f, 237/255.0f,0);
        glClearDepth(1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ASSERT(Observer != nullptr, "ForwardRendererFunction", "Illegal to render world without a camera!");

        /*
        * Get observer matrices
        */
        const glm::mat4x4 viewMatrix = Observer->get_view_matrix();
        const glm::mat4x4 projectionMatrix = Observer->get_projection_matrix();

        /*
        * Render each renderable
        */
        for (unsigned int i = 0; i < Renderables.get_cursor(); i++)
        {
            unsigned int currentTextureSlot = 0;
            const ForwardRenderable* renderable = Renderables[i];
            const SpatialComponent* spatialComponent = renderable->get_owner_entity()->get_component<SpatialComponent>();
            const Mesh* mesh = renderable->get_static_mesh();
            const Material* material = renderable->get_material();
            const ShaderProgram* program = material->get_program();
            const unsigned int programHandle = program->get_program_handle();

            const glm::mat4x4 modelMatrix = spatialComponent->get_model_matrix();
            const glm::mat4x4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;

            /*
            * Set mesh buffer handles
            */
            glBindVertexArray(mesh->get_vertex_array_handle());
            glBindBuffer(GL_ARRAY_BUFFER, mesh->get_vertex_buffer_handle());
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->get_index_buffer_handle());

            /*
            * Set program
            */
            glUseProgram(programHandle);

            /*
            * Set texture parameters
            */
            const Array<MaterialParameter<Texture2D*>>& textureParameters = material->get_texture_parameters();
            for (unsigned int p = 0; p < textureParameters.get_cursor(); p++)
            {
                const MaterialParameter<Texture2D*> textureParameter = textureParameters[p];

                const unsigned int textureSlot = GL_TEXTURE0 + currentTextureSlot;
                glActiveTexture(textureSlot);
                glBindTexture(GL_TEXTURE_2D, textureParameter.Parameter->get_texture_handle());
                glUniform1i(glGetUniformLocation(programHandle, *textureParameter.Name), currentTextureSlot);

                currentTextureSlot++;
            }

            /*
            * Set float parameters
            */
            const Array<MaterialParameter<float>>& floatParameters = material->get_float_parameters();
            for (unsigned int p = 0; p < floatParameters.get_cursor(); p++)
            {
                const MaterialParameter<float> floatParameter = floatParameters[p];

                glUniform1f(glGetUniformLocation(programHandle, *floatParameter.Name), floatParameter.Parameter);
            }

            /*
            * Set point lights
            */
            Array<glm::vec3> pointLightPositions;
            Array<glm::vec3> pointLightColors;
            Array<float> pointLightRanges;
            for (unsigned int p = 0; p < PointLights.get_cursor(); p++)
            {
                const ForwardPointLight* pointLight = PointLights[p];
                pointLightRanges.add(pointLight->get_range());
                pointLightPositions.add(pointLight->get_owner_entity()->get_component<SpatialComponent>()->get_position());
                pointLightColors.add(pointLight->get_color());
            }
            glUniform1i(glGetUniformLocation(programHandle, "f_PointLightCount"), PointLights.get_cursor());
            glUniform1fv(glGetUniformLocation(programHandle, "f_PointLightRanges"), pointLightRanges.get_cursor(), pointLightRanges.get_data());
            glUniform3fv(glGetUniformLocation(programHandle, "f_PointLightPositions"), pointLightPositions.get_cursor(), &pointLightPositions.get_data()->x);
            glUniform3fv(glGetUniformLocation(programHandle, "f_PointLightColors"), pointLightColors.get_cursor(), &pointLightColors.get_data()->x);

            /*
            * Set spot lights
            */
            Array<glm::vec3> spotLightPositions;
            Array<glm::vec3> spotLightColors;
            Array<glm::vec3> spotLightDirs;
            Array<float> spotLightRanges;
            Array<float> spotLightAngles;
            for (unsigned int p = 0; p < SpotLights.get_cursor(); p++)
            {
                const ForwardSpotLight* spotLight = SpotLights[p];
                const SpatialComponent* spatial = spotLight->get_owner_entity()->get_component<SpatialComponent>();
                spotLightRanges.add(spotLight->get_range());
                spotLightAngles.add(spotLight->get_radius());
                spotLightPositions.add(spatial->get_position());
                spotLightDirs.add(spatial->get_forward_vector());
                spotLightColors.add(spotLight->get_color());
            }
            glUniform1i(glGetUniformLocation(programHandle, "f_SpotLightCount"), SpotLights.get_cursor());
            glUniform1fv(glGetUniformLocation(programHandle, "f_SpotLightRanges"), spotLightRanges.get_cursor(), spotLightRanges.get_data());
            glUniform1fv(glGetUniformLocation(programHandle, "f_SpotLightAngles"), spotLightAngles.get_cursor(), spotLightAngles.get_data());
            glUniform3fv(glGetUniformLocation(programHandle, "f_SpotLightPositions"), spotLightPositions.get_cursor(), &spotLightPositions.get_data()->x);
            glUniform3fv(glGetUniformLocation(programHandle, "f_SpotLightDirections"), spotLightDirs.get_cursor(), &spotLightDirs.get_data()->x);
            glUniform3fv(glGetUniformLocation(programHandle, "f_SpotLightColors"), spotLightColors.get_cursor(), &spotLightColors.get_data()->x);

            /*
            * Set constants
            */
            glUniformMatrix4fv(glGetUniformLocation(programHandle, "v_Mvp"),
                1,
                GL_FALSE,
                &mvpMatrix[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(programHandle, "v_Model"),
                1,
                GL_FALSE,
                &modelMatrix[0][0]);

            const glm::vec3 cameraPos = Observer->get_owner_entity()->get_component<SpatialComponent>()->get_position();
            glUniform3fv(glGetUniformLocation(programHandle, "f_ViewPos"),1,&cameraPos.x);

            glDrawElements(GL_TRIANGLES, mesh->get_index_buffer_element_count(), GL_UNSIGNED_INT, nullptr);
        }
    }
    void ForwardRendererFunction::finalize()
    {

    }
}