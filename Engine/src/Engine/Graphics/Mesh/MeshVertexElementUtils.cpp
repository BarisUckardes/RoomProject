#include "MeshVertexElementUtils.h"
#include <GLAD/glad.h>

namespace Engine
{
    unsigned int MeshVertexElementUtils::get_data_size( MeshVertexElementType type)
    {
        switch (type)
        {
            case Engine::MeshVertexElementType::Float:
                return 4;
            case Engine::MeshVertexElementType::Float2:
                return 8;
            case Engine::MeshVertexElementType::Float3:
                return 12;
            case Engine::MeshVertexElementType::Float4:
                return 16;
            case Engine::MeshVertexElementType::Mat3x3:
                return 36;
            case Engine::MeshVertexElementType::Mat4x4:
                return 64;
            default:
                break;
        }
    }
    unsigned int MeshVertexElementUtils::get_component_size(const MeshVertexElementType type)
    {

        switch (type)
        {
            case Engine::MeshVertexElementType::Float:
                return 1;
            case Engine::MeshVertexElementType::Float2:
                return 2;
            case Engine::MeshVertexElementType::Float3:
                return 3;
            case Engine::MeshVertexElementType::Float4:
                return 4;
            case Engine::MeshVertexElementType::Mat3x3:
                return 9;
            case Engine::MeshVertexElementType::Mat4x4:
                return 16;
            default:
                break;
        }
    }
}