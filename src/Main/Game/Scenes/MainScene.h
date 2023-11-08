#pragma once

#include "Engine/Main/EngineHeader.h"
#include "Space/SpaceHeader.h"
#include "Game/Mode/EGameMode.h"

namespace Main::Game
{
    class GameManager;
    class MainScene final: public Engine::Objects::Scene
    {
    public:
        MainScene(const std::string &name, Engine::Window *const window, Engine::Engine *const engine, Space::SpaceManager *const space, GameManager *gameManager);
        ~MainScene();

    public:
        virtual void Update() override;
        virtual void Render() override;

    private:
        void ChangeGameMode(EGameMode gameMode);
        void SwitchState();
        void Pause();
        void Resume();
        Engine::Tools::Events::MemberFunction<MainScene, void> switchState;
        Engine::Tools::Events::MemberFunction<MainScene, EGameMode> changeGameMode;
        Engine::Input::Pressable *escape;
        bool currentState;

    private:
        Space::SpaceManager *const space;
        GameManager *const gameManager;
    };
}