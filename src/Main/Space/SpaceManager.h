#pragma once
#include "Engine/Main/EngineHeader.h"
#include "Space/SpaceTime.h"
#include "Space/GameObjectManager.h"

namespace Main::Space
{
    class SpaceManager
    {
        friend class SpaceMode;

    private:
        SpaceManager(GameObjectManager *objectsManager);
        SpaceManager(const SpaceManager &rhs) = delete;
        SpaceManager(SpaceManager &&rhs) = delete;
        SpaceManager &operator=(const SpaceManager &rhs) = delete;
        SpaceManager &operator=(SpaceManager &&rhs) = delete;
        ~SpaceManager();

    private:
        void Update();

    public:
        SpaceTime *const GetTime();

    private:
        GameObjectManager *const objectsManager;

    private:
        SpaceTime time;
    };
}