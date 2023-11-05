#pragma once

#include "Game/Mode/ModesHeader.h"
#include "Engine/Main/EngineHeader.h"
#include "Editor/GameObjectManager.h"

namespace Main::Game
{
    class GameManager;
}

namespace Main::Editor
{
    class EditorMode: public Game::IGameMode
    {
        friend class Game::GameManager;

    private:
        EditorMode(Engine::UIModule *ui, Engine::Graphics::RenderManager *render, Engine::Graphics::LightManager *lightManager);
        EditorMode(const EditorMode &rhs) = delete;
        EditorMode(EditorMode &&rhs) = delete;
        EditorMode &operator=(const EditorMode &rhs) = delete;
        EditorMode &operator=(EditorMode &&rhs) = delete;
        ~EditorMode();

    public:
        void Start() override final;
        void Update() override final;
        void End() override final;

    public:
        void SetScene(Engine::Objects::Scene *value) override final;

    private:
        Engine::Objects::Scene *scene;
        Engine::UIModule *ui;
        GameObjectManager objectsManager;
    };
}