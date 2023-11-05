#pragma once

#include "Engine/Graphics/Render/RenderPool.h"
#include "Engine/Graphics/Render/RenderUnitBuilder.h"
#include "Engine/Graphics/Light/LightManager.h"

namespace Engine
{
    class GraphicsModule;
}

namespace Engine::Graphics
{
    class RenderManager
    {
        friend class GraphicsModule;

    private:
        RenderManager(Container *container, Camera *camera, LightManager *lightManager);
        RenderManager(const RenderManager &rhs) = delete;
        RenderManager(RenderManager &&rhs) noexcept = delete;
        RenderManager &operator=(const RenderManager &rhs) = delete;
        RenderManager &operator=(RenderManager &&rhs) noexcept = delete;
        ~RenderManager();

    public:
        RenderPool &GetPool();
        RenderUnitBuilder &GetUnitBuilder();

    private:
        RenderPool pool;
        RenderUnitBuilder unitBuilder;
    };
}