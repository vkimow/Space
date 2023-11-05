#include "Engine/Graphics/Render/RenderManager.h"

namespace Engine::Graphics
{
    RenderManager::RenderManager(Container *const container, Camera *camera, LightManager *lightManager)
        : pool(container, camera, lightManager)
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

