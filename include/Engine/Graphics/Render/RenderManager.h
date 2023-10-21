#pragma once

#include "Engine/Graphics/Render/RenderPool.h"
#include "Engine/Graphics/Render/RenderUnitBuilder.h"

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
        RenderManager(Container * const container);
        ~RenderManager();

    public:
        RenderPool &GetPool();
        RenderUnitBuilder &GetUnitBuilder();

    private:
        RenderPool pool;
        RenderUnitBuilder unitBuilder;
    };
}