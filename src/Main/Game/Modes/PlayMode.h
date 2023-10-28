#pragma once
#include "Game/Modes/IGameMode.h"
#include "Engine/Objects/Scene.h"

namespace Main::Game
{
    class PlayMode final: public IGameMode
    {
        PlayMode(Engine::Objects::Scene *scene);
        PlayMode(const PlayMode &rhs) = delete;
        PlayMode(PlayMode &&rhs) = delete;
        PlayMode &operator=(const PlayMode &rhs) = delete;
        PlayMode &operator=(PlayMode &&rhs) = delete;
        ~PlayMode();

    public:
        void Start() override final;
        void Update() override final;
        void End() override final;

    private:
        Engine::Objects::Scene *scene;
    };
}