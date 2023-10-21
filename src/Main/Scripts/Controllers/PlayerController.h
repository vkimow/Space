#pragma once
#include "Engine/Objects/Script.h"
#include "Engine/Objects/GameObject.h"
#include "Engine/Input/InputHeader.h"

namespace Game::Scripts
{
    class PlayerController final: public Engine::Objects::Script
    {
    public:
        PlayerController(Engine::Objects::GameObject *object, 
            Engine::Input::Delta* xInput, Engine::Input::Delta *yInput, Engine::Input::Delta *zInput,
            Engine::Input::Delta* pitchInput, Engine::Input::Delta* yawInput, Engine::Input::Delta* rollInput,
            size_t movementSpeed, size_t rotationSpeed);

        PlayerController(const PlayerController &rhs);
        PlayerController(PlayerController &&rhs) noexcept;

        PlayerController &operator=(const PlayerController &rhs);
        PlayerController &operator=(PlayerController &&rhs) noexcept;

        ~PlayerController();

    protected:
        Engine::Objects::Script *Clone() noexcept override;

    protected:
        void UpdateInner() override;
        size_t GetDefaultPriority() const override;

    private:
        Engine::Input::Delta *xInput;
        Engine::Input::Delta *yInput;
        Engine::Input::Delta *zInput;
        size_t movementSpeed;

        Engine::Input::Delta *pitchInput;
        Engine::Input::Delta *yawInput;
        Engine::Input::Delta *rollInput;
        size_t rotationSpeed;

    private:
        void ClearEvents();

    private:
        const static size_t priority;
    };
}