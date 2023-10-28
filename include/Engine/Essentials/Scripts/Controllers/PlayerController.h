#pragma once
#include "Engine/Objects/Script.h"
#include "Engine/Objects/GameObject.h"
#include "Engine/Input/InputHeader.h"

namespace Engine::Scripts
{
    class PlayerController final: public Objects::Script
    {
    public:
        PlayerController(Objects::GameObject *object, 
            Input::Delta* xInput, Input::Delta *yInput, Input::Delta *zInput,
            Input::Delta* pitchInput, Input::Delta* yawInput, Input::Delta* rollInput,
            size_t movementSpeed, size_t rotationSpeed);

        PlayerController(const PlayerController &rhs);
        PlayerController(PlayerController &&rhs) noexcept;

        PlayerController &operator=(const PlayerController &rhs);
        PlayerController &operator=(PlayerController &&rhs) noexcept;

        ~PlayerController();

    protected:
        Tools::Interfaces::IClonable *Clone() override final;

    protected:
        void UpdateInner() override final;
        size_t GetDefaultPriority() const override final;

    private:
        Input::Delta *xInput;
        Input::Delta *yInput;
        Input::Delta *zInput;
        size_t movementSpeed;

        Input::Delta *pitchInput;
        Input::Delta *yawInput;
        Input::Delta *rollInput;
        size_t rotationSpeed;

    private:
        void ClearEvents();

    private:
        const static size_t priority;
    };
}