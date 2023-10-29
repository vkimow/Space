#include "Space/GameObjectManager.h"

namespace Main::Space
{
    GameObjectManager::GameObjectManager()
        : scene(nullptr)
    {}

    GameObjectManager::~GameObjectManager()
    {
    }

    void GameObjectManager::SetScene(Engine::Objects::Scene *value)
    {
        scene = value;
    }

    void GameObjectManager::UpdateAll()
    {
        Engine::Objects::GameObject *gameObject;
        for (auto it = scene->GetGameObjects().begin(); it != scene->GetGameObjects().end(); ++it)
        {
            gameObject = it->element;
            if (!gameObject->IsActive())
            {
                continue;
            }

            gameObject->Update();
        }
    }

    Engine::Objects::GameObject *const GameObjectManager::GetGameObject(const std::string &name)
    {
        return scene->GetGameObject(name);
    }

    const Engine::Objects::GameObject *const GameObjectManager::GetGameObject(const std::string &name) const
    {
        return scene->GetGameObject(name);
    }

    GameObjectManager::GameObjectsContainer &GameObjectManager::GetGameObjects()
    {
        return scene->GetGameObjects();
    }

    const GameObjectManager::GameObjectsContainer &GameObjectManager::GetGameObjects() const
    {
        return scene->GetGameObjects();
    }
}

