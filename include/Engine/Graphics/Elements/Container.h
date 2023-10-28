#pragma once

#include "Engine/Graphics/Elements/IRendable.h"
#include "Engine/Graphics/Elements/Shader.h"
#include "Engine/Graphics/Elements/Mesh.h"
#include "Engine/Graphics/Elements/Line.h"
#include "Engine/Graphics/Elements/Material.h"
#include "Engine/Graphics/Elements/Texture.h"
#include "Engine/Tools/Log/Logger.h"
#include <unordered_map>
#include <string>
#include <memory>
#include <mutex>

namespace Engine::Graphics
{
    class Container
    {

    private:
        template<typename T>
        struct Inner
        {
            size_t index;
            T *const value;
        };

    public:
        template<typename... Args>
        Shader *const AddShader(const std::string &name, Args... args)
        {
            return AddInner<Shader>(name, shaders, nameToShaders, shadersLock, std::forward<Args>(args)...);
        }

        Shader *const GetShader(size_t index) const;
        Shader *const GetShader(const std::string &name) const;
        size_t GetShaderIndex(Shader *const shader) const;
        size_t GetShaderIndex(const std::string &name) const;

        bool ContainsShader(size_t index) const;
        bool ContainsShader(const std::string &name) const;
        bool ContainsShader(Shader *const shader) const;

    public:
        template<typename... Args>
        Mesh *const AddMesh(const std::string &name, Args... args)
        {
            return AddRendable<Mesh>(name, std::forward<Args>(args)...);
        }

        Mesh *const GetMesh(size_t index) const;
        Mesh *const GetMesh(const std::string &name) const;
        size_t GetMeshIndex(Mesh *const mesh) const;
        size_t GetMeshIndex(const std::string &name) const;

        bool ContainsMesh(size_t index) const;
        bool ContainsMesh(const std::string &name) const;
        bool ContainsMesh(Mesh *const mesh) const;

    public:
        template<typename... Args>
        Line *const AddLine(const std::string &name, Args... args)
        {
            return AddRendable<Line>(name, std::forward<Args>(args)...);
        }

        Line *const GetLine(size_t index) const;
        Line *const GetLine(const std::string &name) const;
        size_t GetLineIndex(Line *const line) const;
        size_t GetLineIndex(const std::string &name) const;

        bool ContainsLine(size_t index) const;
        bool ContainsLine(const std::string &name) const;
        bool ContainsLine(Line *const line) const;

    public:
        template<typename T, typename... Args, typename = std::enable_if_t<std::is_base_of_v<IRendable, T>>>
        T *const AddRendable(const std::string &name, Args... args)
        {
            return AddInner<T, IRendable>(name, rendables, nameToRendables, rendablesLock, std::forward<Args>(args)...);
        }

        template<typename T, typename = std::enable_if_t<std::is_base_of_v<IRendable, T>>>
        T *const GetRendable(size_t index) const
        {
            return static_cast<T *>(rendables[index]);
        }

        template<typename T, typename = std::enable_if_t<std::is_base_of_v<IRendable, T>>>
        T *const GetRendable(const std::string &name) const
        {
            return static_cast<T *>(nameToRendables.at(name).value);
        }

        size_t GetRendableIndex(IRendable *const rendable) const;
        size_t GetRendableIndex(const std::string &name) const;

        bool ContainsRendable(size_t index) const;
        bool ContainsRendable(const std::string &name) const;
        bool ContainsRendable(IRendable *const rendable) const;

    public:
        template<typename... Args>
        Texture *const AddTexture(const std::string &name, Args... args)
        {
            return AddInner<Texture>(name, textures, nameToTextures, texturesLock, std::forward<Args>(args)...);
        }

        Texture *const GetTexture(size_t index) const;
        Texture *const GetTexture(const std::string &name) const;
        size_t GetTextureIndex(Texture *const texture) const;
        size_t GetTextureIndex(const std::string &name) const;

        bool ContainsTexture(size_t index) const;
        bool ContainsTexture(const std::string &name) const;
        bool ContainsTexture(Texture *const texture) const;

    public:
        template<typename... Args>
        Texture *const AddMaterial(const std::string &name, Args... args)
        {
            return AddInner<Material>(name, materials, nameToMaterials, materialsLock, std::forward<Args>(args)...);
        }

        Material *const GetMaterial(size_t index) const;
        Material *const GetMaterial(const std::string &name) const;
        size_t GetMaterialIndex(Material * material) const;
        size_t GetMaterialIndex(const std::string &name) const;

        bool ContainsMaterial(size_t index) const;
        bool ContainsMaterial(const std::string &name) const;
        bool ContainsMaterial(Material *const material) const;

    private:
        template<typename T, typename BaseT = T, typename... Args>
        T *const AddInner(const std::string &name, std::vector<BaseT *> &vector, std::unordered_map<std::string, Inner<BaseT>> &map, std::mutex &mutex, Args... args)
        {
            T *newElement = new T(std::forward<Args>(args)...);
            BaseT *newElementBase = static_cast<BaseT *>(newElement);
            {
                std::lock_guard<std::mutex> guard(mutex);
                vector.push_back(newElementBase);
                size_t index = vector.size() - 1;
                map.emplace(name, Inner<BaseT>(index, newElementBase));
            }
            return newElement;
        }

        template<typename T>
        size_t GetIndexInner(const std::vector<T *> &vector, T *const element) const
        {
            auto it = std::find(vector.begin(), vector.end(), element);
            if (it == vector.end())
            {
                LOG_ERROR("Element Doesn't exists");
            }

            return it - vector.begin();
        }

        template<typename T>
        bool ContainsInner(const std::vector<T *> &vector, T *const element) const
        {
            auto it = std::find(vector.begin(), vector.end(), element);
            return it != vector.end();
        }

    private:
        std::vector<Shader *> shaders;
        std::vector<IRendable *> rendables;
        std::vector<Texture *> textures;
        std::vector<Material *> materials;

        std::unordered_map<std::string, Inner<Shader>> nameToShaders;
        std::unordered_map<std::string, Inner<IRendable>> nameToRendables;
        std::unordered_map<std::string, Inner<Texture>> nameToTextures;
        std::unordered_map<std::string, Inner<Material>> nameToMaterials;

    private:
        std::mutex shadersLock;
        std::mutex rendablesLock;
        std::mutex texturesLock;
        std::mutex materialsLock;
    };
}