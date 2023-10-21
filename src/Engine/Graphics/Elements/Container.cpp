#include "Engine/Graphics/Elements/Container.h"

namespace Engine::Graphics
{
    Shader *const Container::GetShader(size_t index) const
    {
        return shaders[index];
    }

    Shader *const Container::GetShader(const std::string &name) const
    {
        return nameToShaders.at(name).value;
    }

    size_t Container::GetShaderIndex(Shader *const shader) const
    {
        return GetIndexInner<Shader>(shaders, shader);
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
        return ContainsInner<Shader>(shaders, shader);
    }

    Mesh *const Container::GetMesh(size_t index) const
    {
        return meshes[index];
    }

    Mesh *const Container::GetMesh(const std::string &name) const
    {
        return nameToMeshes.at(name).value;
    }

    size_t Container::GetMeshIndex(Mesh *const mesh) const
    {
        return GetIndexInner<Mesh>(meshes, mesh);
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
        return ContainsInner<Mesh>(meshes, mesh);
    }

    Texture *const Container::GetTexture(size_t index) const
    {
        return textures[index];
    }

    Texture *const Container::GetTexture(const std::string &name) const
    {
        return nameToTextures.at(name).value;
    }

    size_t Container::GetTextureIndex(Texture *const texture) const
    {
        return GetIndexInner<Texture>(textures, texture);
    }

    size_t Container::GetTextureIndex(const std::string &name) const
    {
        return nameToTextures.at(name).index;
    }

    bool Container::ContainsTexture(size_t index) const
    {
        return textures.size() > index;
    }

    bool Container::ContainsTexture(const std::string &name) const
    {
        return nameToTextures.contains(name);
    }

    bool Container::ContainsTexture(Texture *const texture) const
    {
        return ContainsInner<Texture>(textures, texture);
    }

    Material *const Container::GetMaterial(size_t index) const
    {
        return materials[index];
    }

    Material *const Container::GetMaterial(const std::string &name) const
    {
        return nameToMaterials.at(name).value;
    }

    size_t Container::GetMaterialIndex(Material *const material) const
    {
        return GetIndexInner<Material>(materials, material);
    }

    size_t Container::GetMaterialIndex(const std::string &name) const
    {
        return nameToMaterials.at(name).index;
    }

    bool Container::ContainsMaterial(size_t index) const
    {
        return materials.size() > index;
    }

    bool Container::ContainsMaterial(const std::string &name) const
    {
        return nameToMaterials.contains(name);
    }

    bool Container::ContainsMaterial(Material *const material) const
    {
        return ContainsInner<Material>(materials, material);
    }
}