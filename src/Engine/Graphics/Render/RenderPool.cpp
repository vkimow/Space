#include "Engine/Graphics/Render/RenderPool.h"
#include <glm/gtc/type_ptr.hpp>

namespace Engine::Graphics
{
    RenderPool::RenderPool(Container *const container)
        : container(container)
        , queue()
        , shadersLock()
        , meshesLock()
        , elementsLock()
    {}

    RenderPool::~RenderPool()
    {}

    void RenderPool::RenderAll()
    {
        for (auto it = queue.begin(); it != queue.end(); ++it)
        {
            Shader *shader = container->GetShader(it->first);
            MeshToElements &meshToElement = it->second;
            shader->Use();

            glm::mat4 projectionMatrix = camera->GetProjectionMatrix();
            glm::mat4 viewMatrix = camera->GetViewMatrix();

            glUniformMatrix4fv(shader->GetProjectionUniform(), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
            glUniformMatrix4fv(shader->GetViewUniform(), 1, GL_FALSE, glm::value_ptr(viewMatrix));

            for (auto it2 = meshToElement.begin(); it2 != meshToElement.end(); ++it2)
            {
                Mesh *mesh = container->GetMesh(it2->first);
                Elements &elements = it2->second;

                mesh->StartRender();

                for (auto it3 = elements.begin(); it3 != elements.end(); ++it3)
                {
                    Material *material;
                    Texture *texture;
                    if (it3->material)
                    {
                        material = container->GetMaterial(it3->material.GetIndex());
                    }
                    if (it3->texture)
                    {
                        texture = container->GetTexture(it3->texture.GetIndex());
                    }

                    glm::mat4 transformMatrix = it3->transform->GetTransformMatrix();
                    glUniformMatrix4fv(shader->GetModelUniform(), 1, GL_FALSE, glm::value_ptr(transformMatrix));
                    mesh->Render();
                }

                mesh->EndRender();
            }

            shader->Validate();
        }
    }

    void RenderPool::SetCamera(Camera *const value)
    {
        camera = value;
    }

    void RenderPool::AddRenderUnit(const RenderUnit &element)
    {
        if (!element.ContainsShader() || !element.ContainsMesh() || !element.ContainsTransform())
        {
            return;
        }

        {
            std::lock_guard<std::mutex> guard(shadersLock);
            if (!queue.contains(element.GetShaderIndex()))
            {
                queue.emplace(element.GetShaderIndex(), MeshToElements());
            }
        }

        MeshToElements &meshes = queue[element.GetShaderIndex()];
        {
            std::lock_guard<std::mutex> guard(meshesLock);
            if (!meshes.contains(element.GetMeshIndex()))
            {
                meshes.emplace(element.GetMeshIndex(), Elements());
            }
        }

        Elements &elements = meshes[element.GetMeshIndex()];
        {
            std::lock_guard<std::mutex> guard(elementsLock);
            elements.emplace_back(element.GetTexture(), element.GetMaterial(), element.GetTransform());
        }
    }
}