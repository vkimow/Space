#pragma once

#include "Engine/Graphics/Shader.h"
#include "Engine/Graphics/Mesh.h"
#include "Engine/Graphics/Material.h"
#include <unordered_map>
#include <string>
#include <mutex>

namespace Engine::Graphics
{
    class Container
    {
        struct ShaderInner
        {
            size_t index;
            Shader *const shader;
        };

        struct MeshInner
        {
            size_t index;
            Mesh *const mesh;
        };

    public:
        template<typename... Args>
        Shader* const AddShader(const std::string &name, Args... args)
        {
            Shader *shader = new Shader(std::forward<Args>(args)...);
            size_t index = 0;
            {
                std::lock_guard<std::mutex> guard(shadersLock);
                shaders.push_back(shader);
                index = shaders.size() - 1;
            }
            {
                std::lock_guard<std::mutex> guard(nameToShadersLock);
                nameToShaders.insert(std::make_pair(name, ShaderInner(index, shader)));
            }
            return shader;
        }

        Shader *const GetShader(size_t index) const;
        Shader *const GetShader(const std::string &name) const;
        size_t GetShaderIndex(Shader *const shader) const;
        size_t GetShaderIndex(const std::string &name) const;

        bool ContainsShader(size_t index) const;
        bool ContainsShader(const std::string &name) const;
        bool ContainsShader(Shader *const shader) const;

        template<typename... Args>
        Mesh* const AddMesh(const std::string &name, Args... args)
        {
            Mesh *mesh = new Mesh(std::forward<Args>(args)...);
            size_t index = 0;
            {
                std::lock_guard<std::mutex> guard(meshesLock);
                meshes.push_back(mesh);
                index = meshes.size() - 1;
            }
            {
                std::lock_guard<std::mutex> guard(nameToMeshesLock);
                nameToMeshes.insert(std::make_pair(name, MeshInner(index, mesh)));
            }
            return mesh;
        }

        Mesh *const GetMesh(size_t index) const;
        Mesh *const GetMesh(const std::string &name) const;
        size_t GetMeshIndex(Mesh *const mesh) const;
        size_t GetMeshIndex(const std::string &name) const;

        bool ContainsMesh(size_t index) const;
        bool ContainsMesh(const std::string &name) const;
        bool ContainsMesh(Mesh *const mesh) const;

    private:
        std::vector<Shader *> shaders;
        std::vector<Mesh *> meshes;
        std::unordered_map<std::string, ShaderInner> nameToShaders;
        std::unordered_map<std::string, MeshInner> nameToMeshes;

    private:
        std::mutex shadersLock;
        std::mutex meshesLock;
        std::mutex nameToShadersLock;
        std::mutex nameToMeshesLock;
    };
}