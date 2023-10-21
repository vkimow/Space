#include "Engine/Graphics/Container.h"
#include "Engine/Tools/Log/Logger.h"

namespace Engine::Graphics
{
    Shader *const Container::GetShader(size_t index) const
    {
        return shaders[index];
    }

    Shader *const Container::GetShader(const std::string &name) const
    {
        return nameToShaders.at(name).shader;
    }

    size_t Container::GetShaderIndex(Shader *const shader) const
    {
        auto it = std::find(shaders.begin(), shaders.end(), shader);
        if (it == shaders.end())
        {
            LOG_ERROR("Shader doesn't exists");
        }

        return it - shaders.begin();
    }

    size_t Container::GetShaderIndex(const std::string &name) const
    {
        return nameToShaders.at(name).index;
    }

    bool Container::ContainsShader(size_t index) const
    {
        return shaders.size() > index;
    }

    bool Container::ContainsShader(const std::string &name) const
    {
        return nameToShaders.contains(name);
    }

    bool Container::ContainsShader(Shader *const shader) const
    {
        auto it = std::find(shaders.begin(), shaders.end(), shader);
        return it != shaders.end();
    }

    Mesh *const Container::GetMesh(size_t index) const
    {
        return meshes[index];
    }

    Mesh *const Container::GetMesh(const std::string &name) const
    {
        return nameToMeshes.at(name).mesh;
    }

    size_t Container::GetMeshIndex(Mesh *const mesh) const
    {
        auto it = std::find(meshes.begin(), meshes.end(), mesh);
        if (it == meshes.end())
        {
            LOG_ERROR("Shader doesn't exists");
        }

        return it - meshes.begin();
    }

    size_t Container::GetMeshIndex(const std::string &name) const
    {
        return nameToMeshes.at(name).index;
    }

    bool Container::ContainsMesh(size_t index) const
    {
        return meshes.size() > index;
    }

    bool Container::ContainsMesh(const std::string &name) const
    {
        return nameToMeshes.contains(name);
    }

    bool Container::ContainsMesh(Mesh *const mesh) const
    {
        auto it = std::find(meshes.begin(), meshes.end(), mesh);
        return it != meshes.end();
    }
}