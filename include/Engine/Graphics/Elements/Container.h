#pragma once

#include "Engine/Graphics/Elements/Shader.h"
#include "Engine/Graphics/Elements/Interfaces/InterfacesHeader.h"
#include "Engine/Graphics/Elements/Rendables/RendablesHeader.h"
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
            T *value;
        };

    public:
        Container();
        ~Container();

    public:
        template<typename... Args>
        Shader *const AddShader(const std::string &name, Args... args)
        {
            LOG_DEBUG("Add Shader {}", name);
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
            LOG_DEBUG("Add Mesh {}", name);
            return AddRendable<Mesh>(name, std::forward<Args>(args)...);
        }

        void AddMesh(const std::string &name, Mesh *newMesh)
        {
            LOG_DEBUG("Add Mesh {}", name);
            AddRendable<Mesh>(name, newMesh);
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

        void AddLine(const std::string &name, Line* newLine)
        {
            AddRendable<Line>(name, newLine);
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
        void AddRendable(const std::string &name, T* newRendable)
        {
            return AddInner<T, IRendable>(name, rendables, nameToRendables, rendablesLock, newRendable);
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
        template<typename T, typename... Args, typename = std::enable_if_t<std::is_base_of_v<ITexture, T>>>
        T *const AddTexture(const std::string &name, Args... args)
        {
            LOG_DEBUG("Add Texture {}", name);
            return AddInner<T, ITexture>(name, textures, nameToTextures, texturesLock, std::forward<Args>(args)...);
        }

        template<typename T = ITexture, typename = std::enable_if_t<std::is_base_of_v<ITexture, T>>>
        T *const GetTexture(size_t index) const
        {
            return static_cast<T *>(textures[index]);
        }

        template<typename T = ITexture, typename = std::enable_if_t<std::is_base_of_v<ITexture, T>>>
        T *const GetTexture(const std::string &name) const
        {
            return static_cast<T *>(nameToTextures.at(name).value);
        }

        size_t GetTextureIndex(ITexture *const texture) const;
        size_t GetTextureIndex(const std::string &name) const;

        bool ContainsTexture(size_t index) const;
        bool ContainsTexture(const std::string &name) const;
        bool ContainsTexture(ITexture *const texture) const;

    public:
        template<typename T, typename... Args, typename = std::enable_if_t<std::is_base_of_v<IMaterial, T>>>
        T *const AddMaterial(const std::string &name, Args... args)
        {
            LOG_DEBUG("Add Material {}", name);
            return AddInner<T, IMaterial>(name, materials, nameToMaterials, materialsLock, std::forward<Args>(args)...);
        }

        template<typename T = IMaterial, typename = std::enable_if_t<std::is_base_of_v<IMaterial, T>>>
        T *const GetMaterial(size_t index) const
        {
            return static_cast<T *>(materials[index]);
        }

        template<typename T = IMaterial, typename = std::enable_if_t<std::is_base_of_v<IMaterial, T>>>
        T *const GetMaterial(const std::string &name) const
        {
            return static_cast<T *>(nameToMaterials.at(name).value);
        }

        size_t GetMaterialIndex(IMaterial *material) const;
        size_t GetMaterialIndex(const std::string &name) const;

        bool ContainsMaterial(size_t index) const;
        bool ContainsMaterial(const std::string &name) const;
        bool ContainsMaterial(IMaterial *const material) const;

    private:
        template<typename T, typename BaseT = T, typename... Args>
        T *const AddInner(const std::string &name, std::vector<BaseT *> &vector, std::unordered_map<std::string, Inner<BaseT>> &map, std::mutex &mutex, Args... args)
        {
            T *newElement = new T(std::forward<Args>(args)...);
            {
                std::lock_guard<std::mutex> guard(mutex);

                if (map.contains(name))
                {
                    auto pos = std::find(vector.begin(), vector.end(), map[name].value);
                    BaseT *elementToDelete = *pos;
                    *pos = newElement;
                    delete elementToDelete;
                    map[name].value = newElement;
                }
                else
                {
                    vector.push_back(newElement);
                    size_t index = vector.size() - 1;
                    map.emplace(name, Inner<BaseT>(index, newElement));
                }
            }
            return newElement;
        }

        template<typename T, typename BaseT = T>
        void AddInner(const std::string &name, std::vector<BaseT *> &vector, std::unordered_map<std::string, Inner<BaseT>> &map, std::mutex &mutex, T *newElement)
        {
            std::lock_guard<std::mutex> guard(mutex);
            if (map.contains(name))
            {
                auto pos = std::find(vector.begin(), vector.end(), map[name].value);
                BaseT *elementToDelete = *pos;
                *pos = newElement;
                delete elementToDelete;
                map[name].value = newElement;
            }
            else
            {
                vector.push_back(newElement);
                size_t index = vector.size() - 1;
                map.emplace(name, Inner<BaseT>(index, newElement));
            }
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

        template<typename T>
        void Clear(std::vector<T *> &vector, std::unordered_map<std::string, Inner<T>> &map, std::mutex &mutex)
        {
            std::lock_guard<std::mutex> guard(mutex);
            for (auto it = vector.begin(); it != vector.end(); ++it)
            {
                delete *it;
            }

            vector.clear();
            map.clear();
        }

    private:
        std::vector<Shader *> shaders;
        std::vector<IRendable *> rendables;
        std::vector<ITexture *> textures;
        std::vector<IMaterial *> materials;

        std::unordered_map<std::string, Inner<Shader>> nameToShaders;
        std::unordered_map<std::string, Inner<IRendable>> nameToRendables;
        std::unordered_map<std::string, Inner<ITexture>> nameToTextures;
        std::unordered_map<std::string, Inner<IMaterial>> nameToMaterials;

    private:
        std::mutex shadersLock;
        std::mutex rendablesLock;
        std::mutex texturesLock;
        std::mutex materialsLock;
    };
}