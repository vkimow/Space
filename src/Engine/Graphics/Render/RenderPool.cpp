#include "Engine/Graphics/Render/RenderPool.h"
#include <glm/gtc/type_ptr.hpp>

namespace Engine::Graphics
{
    RenderPool::RenderPool(Container *const container)
        : container(container)
        , queue()
        , camera(nullptr)
        , shadersLock()
        , rendablesLock()
        , elementsLock()
    {}

    RenderPool::~RenderPool()
    {}

    void RenderPool::RenderAll()
    {
        for (auto it = queue.begin(); it != queue.end(); ++it)
        {
            Shader *shader = container->GetShader(it->first);
            IRendable *rendable = nullptr;

            RendableToElements &rendableToElements = it->second;
            shader->Use();

            glm::mat4 projectionMatrix = camera->GetProjectionMatrix();
            glm::mat4 viewMatrix = camera->GetViewMatrix();
            glm::mat4 viewProjectionMatrix = camera->GetViewProjectionMatrix();
            glm::vec4 color(0.0f, 1.0f, 1.0f, 1.0f);

            glUniformMatrix4fv(shader->GetProjectionUniform(), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
            glUniformMatrix4fv(shader->GetViewUniform(), 1, GL_FALSE, glm::value_ptr(viewMatrix));
            glUniformMatrix4fv(shader->GetViewProjectionUniform(), 1, GL_FALSE, glm::value_ptr(viewProjectionMatrix));
            glUniform4fv(shader->GetColorUniform(), 1, glm::value_ptr(color));

            for (auto it2 = rendableToElements.begin(); it2 != rendableToElements.end(); ++it2)
            {
                rendable = container->GetRendable<IRendable>(it2->first);
                Elements &elements = it2->second;

                rendable->StartRender();

                for (auto it3 = elements.begin(); it3 != elements.end(); ++it3)
                {
                    if (it3->material)
                    {
                        Material *material = container->GetMaterial(it3->material.GetIndex());
                    }
                    if (it3->texture)
                    {
                        Texture *texture = container->GetTexture(it3->texture.GetIndex());
                    }

                    glm::mat4 transformMatrix = it3->transform->GetTransformMatrix();
                    glUniformMatrix4fv(shader->GetModelUniform(), 1, GL_FALSE, glm::value_ptr(transformMatrix));
                    rendable->Render();
                }

                rendable->EndRender();
            }

            shader->Validate();
        }

        queue.clear();
    }

    void RenderPool::SetCamera(Camera *const value)
    {
        camera = value;
    }

    void RenderPool::AddRenderUnit(const RenderUnit &element)
    {
        if (!element.ContainsShader() || !element.ContainsRendable() || !element.ContainsTransform())
        {
            return;
        }

        {
            std::lock_guard<std::mutex> guard(shadersLock);
            if (!queue.contains(element.GetShaderIndex()))
            {
                queue.emplace(element.GetShaderIndex(), RendableToElements());
            }
        }

        RendableToElements &rendables = queue[element.GetShaderIndex()];
        {
            std::lock_guard<std::mutex> guard(rendablesLock);
            if (!rendables.contains(element.GetRendableIndex()))
            {
                rendables.emplace(element.GetRendableIndex(), Elements());
            }
        }

        Elements &elements = rendables[element.GetRendableIndex()];
        {
            std::lock_guard<std::mutex> guard(elementsLock);
            elements.emplace_back(element.GetTexture(), element.GetMaterial(), element.GetTransform());
        }
    }
}