#pragma once

#include "Game/Mode/ModesHeader.h"
#include "Engine/Main/EngineHeader.h"
#include "Space/GameObjectManager.h"
#include "Space/SpaceManager.h"

namespace Main::Game
{
    class GameManager;
}

namespace Main::Space
{
    class SpaceMode: public Game::IGameMode
    {
        friend class Game::GameManager;

    private:
        SpaceMode(Engine::UIModule *ui, Engine::GraphicsModule *graphics, Engine::InputModule *input);
        SpaceMode(const SpaceMode &rhs) = delete;
        SpaceMode(SpaceMode &&rhs) = delete;
        SpaceMode &operator=(const SpaceMode &rhs) = delete;
        SpaceMode &operator=(SpaceMode &&rhs) = delete;
        ~SpaceMode();

    public:
        void Start() override final;
        void Update() override final;
        void End() override final;

    public:
        void SetScene(Engine::Objects::Scene *value) override final;

    public:
        SpaceManager &GetSpaceManager();
        const SpaceManager &GetSpaceManager() const;

    private:
        Engine::Objects::Scene *scene;
        Engine::UIModule * const ui;
        Engine::InputModule * const input;
        GameObjectManager objectsManager;
        SpaceManager spaceManager;
    };
}