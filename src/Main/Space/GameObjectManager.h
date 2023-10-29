#pragma once

#include <string>
#include "Engine/Main/EngineHeader.h"
#include "Editor/Menus/GameObjects/GameObjectsMenuHeader.h"

namespace Main::Space
{
    class GameObjectManager
    {
        using GameObjectsContainer = Engine::Tools::Structs::MapWithPriority<std::string, Engine::Objects::GameObject>;

    public:
        GameObjectManager();
        GameObjectManager(const GameObjectManager &rhs) = delete;
        GameObjectManager(GameObjectManager &&rhs) noexcept = delete;
        GameObjectManager &operator=(const GameObjectManager &rhs) = delete;
        GameObjectManager &operator=(GameObjectManager &&rhs) noexcept = delete;
        ~GameObjectManager();

    public:
        void SetScene(Engine::Objects::Scene *value);

    public:
        void UpdateAll();

    public:
        Engine::Objects::GameObject *const GetGameObject(const std::string &name);
        const Engine::Objects::GameObject *const GetGameObject(const std::string &name) const;

    public:
        GameObjectsContainer &GetGameObjects();
        const GameObjectsContainer &GetGameObjects() const;

    private:
        Engine::Objects::Scene *scene;
    };
}