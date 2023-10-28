#pragma once

#include <unordered_map>
#include "Engine/Objects/Transform.h"
#include "Engine/Graphics/Render/RenderElement.h"
#include "Engine/Graphics/Render/RenderUnit.h"
#include "Engine/Graphics/Elements/Container.h"
#include "Engine/Graphics/Camera/Camera.h"
#include <mutex>

namespace Engine::Graphics
{
    class RenderPool
    {
        friend class RenderManager;

        struct PoolElement
        {
            RenderElement texture;
            RenderElement material;
            Objects::Transform *transform;
        };

        using RendableIndex = size_t;
        using ShaderIndex = size_t;

        using Elements = std::vector<PoolElement>;
        using RendableToElements = std::unordered_map<RendableIndex, Elements>;
        using ShaderToMeshes = std::unordered_map<ShaderIndex, RendableToElements>;
        using RenderQueue = ShaderToMeshes;

    private:
        RenderPool(Container *const container);
        RenderPool() = delete;
        RenderPool(const RenderPool &rhs) = delete;
        RenderPool(RenderPool &&rhs) = delete;
        RenderPool &operator=(const RenderPool &rhs) = delete;
        RenderPool &operator=(RenderPool &&rhs) = delete;
        ~RenderPool();

    public:
        void RenderAll();
        void SetCamera(Camera * const value);

    public:
        void AddRenderUnit(auto first, auto last)
        {
            for (auto it = first; it != last; ++it)
            {
                AddRenderUnit(*it);
            }
        }
        void AddRenderUnit(const RenderUnit &element);

    private:
        RenderQueue queue;
        Container *const container;
        Camera * camera;

    private:
        std::mutex shadersLock;
        std::mutex rendablesLock;
        std::mutex elementsLock;
    };
}