#include "Material.h"
#include <Engine/Graphics/Shader/ShaderProgram.h>
namespace Engine
{
    Material::Material(ShaderProgram* program)
    {
        Program = program;
    }
    const Array<MaterialParameter<Texture2D*>>& Material::get_texture_parameters() const
    {
        return Textures;
    }
    const Array<MaterialParameter<float>>& Material::get_float_parameters() const
    {
        return Floats;
    }
    const Array<MaterialParameter<glm::vec3>>& Material::get_vec3_parameters() const
    {
        return Vector3s;
    }
    ShaderProgram* Material::get_program() const
    {
        return Program;
    }
    void Material::set_texture_parameter(const String& parameterName, Texture2D* parameter)
    {
        /*
        * Validate if this is anew parameter
        */
        int parameterIndex = -1;
        for (unsigned int i = 0; i < Textures.get_cursor(); i++)
        {
            if (Textures[i].Name == parameterName)
            {
                parameterIndex = i;
                break;
            }
        }

        if (parameterIndex == -1) // parameter does not exists
        {
            MaterialParameter<Texture2D*> textureParameter = {};
            textureParameter.Name = parameterName;
            textureParameter.Parameter = parameter;
            Textures.add(textureParameter);
        }
        else
        {
            Textures[parameterIndex].Parameter = parameter;
        }
    }
    void Material::set_float_parameter(const String& parameterName, const float parameter)
    {
        /*
         * Validate if this is anew parameter
        */
        int parameterIndex = -1;
        for (unsigned int i = 0; i < Floats.get_cursor(); i++)
        {
            if (Floats[i].Name == parameterName)
            {
                parameterIndex = i;
                break;
            }
        }

        if (parameterIndex == -1) // parameter does not exists
        {
            MaterialParameter<float> floatParameter = {};
            floatParameter.Name = parameterName;
            floatParameter.Parameter = parameter;
            Floats.add(floatParameter);
        }
        else
        {
            Floats[parameterIndex].Parameter = parameter;
        }
    }
    void Material::set_vec3_parameter(const String& parameterName, const glm::vec3& parameter)
    {

        /*
         * Validate if this is anew parameter
        */
        int parameterIndex = -1;
        for (unsigned int i = 0; i < Vector3s.get_cursor(); i++)
        {
            if (Vector3s[i].Name == parameterName)
            {
                parameterIndex = i;
                break;
            }
        }

        if (parameterIndex == -1) // parameter does not exists
        {
            MaterialParameter<glm::vec3> vec3Parameter = {};
            vec3Parameter.Name = parameterName;
            vec3Parameter.Parameter = parameter;
            Vector3s.add(vec3Parameter);
        }
        else
        {
            Vector3s[parameterIndex].Parameter = parameter;
        }
    }
    int Material::get_paramater_index(const String& name)
    {
        return 0;
    }
}