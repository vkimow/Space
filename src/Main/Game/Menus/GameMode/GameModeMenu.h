#pragma once
#include "Engine/UI/Menu/Menu.h"
#include "Engine/UI/Menu/MenuContainer.h"
#include "Game/Modes/EGameMode.h"
#include "Engine/Tools/Events/MemberFunction.h"

namespace Main::Game
{
    class GameManager;
    class GameModeMenu final: public Engine::UI::Menu
    {
        friend class Engine::UI::MenuContainer;
        friend class GameModeMenuUI;

    private:
        GameModeMenu(GameManager *gameManager);
        GameModeMenu(const GameModeMenu &rhs) = delete;
        GameModeMenu(GameModeMenu &&rhs) noexcept = delete;
        GameModeMenu &operator=(const GameModeMenu &rhs) = delete;
        GameModeMenu &operator=(GameModeMenu &&rhs) noexcept = delete;
        ~GameModeMenu();

    public:
        void Update() override final;
        size_t GetDefaultPriority() const override final;

    private:
        GameManager *const gameManager;
        EGameMode mode;

    private:
        void SetGameMode(EGameMode value);
    private:
        Engine::Tools::Events::MemberFunction<GameModeMenu, EGameMode> setGameMode;

    private:
        static size_t priority;
    };
}