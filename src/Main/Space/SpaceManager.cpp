#include "Space/SpaceManager.h"
#include "Space/Menus/MenusHeader.h"

namespace Main::Space
{
    SpaceManager::SpaceManager(GameObjectManager *objectsManager)
        : objectsManager(objectsManager)
        , time()
    {}

    SpaceManager::~SpaceManager()
    {}

    void SpaceManager::Update()
    {
        time.Update();
    }

    SpaceTime *const SpaceManager::GetTime()
    {
        return &time;
    }
}