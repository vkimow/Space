#include "Engine/Graphics/Render/RenderManager.h"

namespace Engine::Graphics
{
    RenderManager::RenderManager(Container *const container)
        : pool(container)
        , unitBuilder(container)
    {}

    RenderManager::~RenderManager()
    {}

    RenderPool &RenderManager::GetPool()
    {
        return pool;
    }

    RenderUnitBuilder &RenderManager::GetUnitBuilder()
    {
        return unitBuilder;
    }
}

