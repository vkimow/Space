#include "Engine/Graphics/Elements/Container.h"

namespace Engine::Graphics
{
    Container::Container()
        : shaders()
        , rendables()
        , textures()
        , materials()
        , nameToShaders()
        , nameToRendables()
        , nameToTextures()
        , nameToMaterials()
        , shadersLock()
        , rendablesLock()
        , texturesLock()
        , materialsLock()
    {}

    Container::~Container()
    {
        Clear<Shader>(shaders, nameToShaders, shadersLock);
        Clear<IRendable>(rendables, nameToRendables, rendablesLock);
        Clear<ITexture>(textures, nameToTextures, texturesLock);
        Clear<IMaterial>(materials, nameToMaterials, materialsLock);
    }

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

    size_t Container::GetTextureIndex(ITexture *const texture) const
    {
        return GetIndexInner<ITexture>(textures, texture);
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

    bool Container::ContainsTexture(ITexture *const texture) const
    {
        return ContainsInner<ITexture>(textures, texture);
    }

    size_t Container::GetMaterialIndex(IMaterial * const material) const
    {
        return GetIndexInner<IMaterial>(materials, material);
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

    bool Container::ContainsMaterial(IMaterial *const material) const
    {
        return ContainsInner<IMaterial>(materials, material);
    }

    Line *const Container::GetLine(size_t index) const
    {
        return GetRendable<Line>(index);
    }

    Line *const Container::GetLine(const std::string &name) const
    {
        return GetRendable<Line>(name);
    }

    size_t Container::GetLineIndex(Line *const line) const
    {
        return GetRendableIndex(line);
    }

    size_t Container::GetLineIndex(const std::string &name) const
    {
        return GetRendableIndex(name);
    }

    bool Container::ContainsLine(size_t index) const
    {
        return ContainsRendable(index);
    }

    bool Container::ContainsLine(const std::string &name) const
    {
        return ContainsRendable(name);
    }

    bool Container::ContainsLine(Line *const line) const
    {
        return ContainsRendable(line);
    }

    Mesh *const Container::GetMesh(size_t index) const
    {
        return GetRendable<Mesh>(index);
    }

    Mesh *const Container::GetMesh(const std::string &name) const
    {
        return GetRendable<Mesh>(name);
    }

    size_t Container::GetMeshIndex(Mesh *const mesh) const
    {
        return GetRendableIndex(mesh);
    }

    size_t Container::GetMeshIndex(const std::string &name) const
    {
        return GetRendableIndex(name);
    }

    bool Container::ContainsMesh(size_t index) const
    {
        return ContainsRendable(index);
    }

    bool Container::ContainsMesh(const std::string &name) const
    {
        return ContainsRendable(name);
    }

    bool Container::ContainsMesh(Mesh *const mesh) const
    {
        return ContainsRendable(mesh);
    }

    size_t Container::GetRendableIndex(IRendable *const rendable) const
    {
        return GetIndexInner<IRendable>(rendables, rendable);
    }

    size_t Container::GetRendableIndex(const std::string &name) const
    {
        return nameToRendables.at(name).index;
    }

    bool Container::ContainsRendable(size_t index) const
    {
        return rendables.size() > index;
    }

    bool Container::ContainsRendable(const std::string &name) const
    {
        return nameToRendables.contains(name);
    }

    bool Container::ContainsRendable(IRendable *const rendable) const
    {
        return ContainsInner<IRendable>(rendables, rendable);
    }
}