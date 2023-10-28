#pragma once
#include "Game/Modes/IGameMode.h"
#include "Engine/Objects/Scene.h"

namespace Main::Game
{
    class GameManager;
    class EditMode final: public IGameMode
    {
        EditMode(GameManager* manager, Engine::Objects::Scene *scene);
        EditMode(const EditMode &rhs) = delete;
        EditMode(EditMode &&rhs) = delete;
        EditMode &operator=(const EditMode &rhs) = delete;
        EditMode &operator=(EditMode &&rhs) = delete;
        ~EditMode();

    public:
        void Start() override final;
        void Update() override final;
        void End() override final;

    private:
        Engine::Objects::Scene *scene;
        GameManager *manager;
    };
}