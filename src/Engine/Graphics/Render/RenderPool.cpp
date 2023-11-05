#include "Engine/Graphics/Render/RenderPool.h"
#include <glm/gtc/type_ptr.hpp>
#include "Engine/Graphics/Elements/Interfaces/InterfacesHeader.h"

namespace Engine::Graphics
{
    RenderPool::RenderPool(Container *const container, Camera* camera, LightManager *lightManager)
        : container(container)
        , queue()
        , camera(camera)
        , lightManager(lightManager)
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
            camera->Use(shader);
            lightManager->Use(shader);

            for (auto it2 = rendableToElements.begin(); it2 != rendableToElements.end(); ++it2)
            {
                rendable = container->GetRendable<IRendable>(it2->first);
                Elements &elements = it2->second;

                rendable->StartRender();

                for (auto it3 = elements.begin(); it3 != elements.end(); ++it3)
                {
                    if (it3->material)
                    {
                        IMaterial *material = container->GetMaterial(it3->material.GetIndex());
                        material->Use(shader);
                    }
                    if (it3->texture)
                    {
                        ITexture *texture = container->GetTexture(it3->texture.GetIndex());
                        texture->Use(shader);
                    }

                    it3->modelMatrix->Use(shader);
                    rendable->Render();
                }

                rendable->EndRender();
            }

            shader->Validate();
        }

        queue.clear();
    }

    void RenderPool::AddRenderUnit(const RenderUnit &element)
    {
        if (!element.ContainsShader() || !element.ContainsRendable() || !element.ContainsModelMatrix())
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
            elements.emplace_back(element.GetTexture(), element.GetMaterial(), element.GetModelMatrix());
        }
    }
}