#pragma once
#include "Main/Scripts/Controllers/PlayerController.h"
#include "Engine/Objects/GameObjectTools.h"
#include "Engine/Main/Modules/TimeModule.h"

namespace Game::Scripts
{
    PlayerController::PlayerController(Engine::Objects::GameObject *object,
        Engine::Input::Delta *xInput, Engine::Input::Delta *yInput, Engine::Input::Delta *zInput,
        Engine::Input::Delta *pitchInput, Engine::Input::Delta *yawInput, Engine::Input::Delta *rollInput,
        size_t movementSpeed, size_t rotationSpeed)
        : Script(object)
        , xInput(xInput)
        , yInput(yInput)
        , zInput(zInput)
        , pitchInput(pitchInput)
        , yawInput(yawInput)
        , rollInput(rollInput)
        , movementSpeed(movementSpeed)
        , rotationSpeed(rotationSpeed)
    {}

    PlayerController::PlayerController(const PlayerController &rhs)
        : Script(rhs)
        , xInput(rhs.xInput)
        , yInput(rhs.yInput)
        , zInput(rhs.zInput)
        , pitchInput(rhs.pitchInput)
        , yawInput(rhs.yawInput)
        , rollInput(rhs.rollInput)
        , movementSpeed(rhs.movementSpeed)
        , rotationSpeed(rhs.rotationSpeed)
    {}

    PlayerController::PlayerController(PlayerController &&rhs) noexcept
        : Script(std::move(rhs))
        , xInput(rhs.xInput)
        , yInput(rhs.yInput)
        , zInput(rhs.zInput)
        , pitchInput(rhs.pitchInput)
        , yawInput(rhs.yawInput)
        , rollInput(rhs.rollInput)
        , movementSpeed(rhs.movementSpeed)
        , rotationSpeed(rhs.rotationSpeed)
    {
        rhs.ClearEvents();
    }

    PlayerController &PlayerController::operator=(const PlayerController &rhs)
    {
        Script::operator=(rhs);
        xInput = rhs.xInput;
        yInput = rhs.yInput;
        zInput = rhs.zInput;
        pitchInput = rhs.pitchInput;
        yawInput = rhs.yawInput;
        rollInput = rhs.rollInput;
        movementSpeed = rhs.movementSpeed;
        rotationSpeed = rhs.rotationSpeed;
        return *this;
    }

    PlayerController &PlayerController::operator=(PlayerController &&rhs) noexcept
    {
        Script::operator=(std::move(rhs));
        xInput = rhs.xInput;
        yInput = rhs.yInput;
        zInput = rhs.zInput;
        pitchInput = rhs.pitchInput;
        yawInput = rhs.yawInput;
        rollInput = rhs.rollInput;
        movementSpeed = rhs.movementSpeed;
        rotationSpeed = rhs.rotationSpeed;
        rhs.ClearEvents();
        return *this;
    }

    PlayerController::~PlayerController()
    {
        ClearEvents();
    }

    Engine::Objects::Script *PlayerController::Clone() noexcept
    {
        return new PlayerController(*this);
    }

    void PlayerController::UpdateInner()
    {
        if (!(xInput->IsZero() && yInput->IsZero() && zInput->IsZero()))
        {
            glm::vec3 moveDelta(xInput->GetDelta(), -yInput->GetDelta(), -zInput->GetDelta());
            moveDelta *= movementSpeed * Engine::TimeModule::GetDeltaTime();
            Engine::Objects::MoveInOrientation(GetGameObject(), moveDelta);
        }

        if (!(pitchInput->IsZero() && yawInput->IsZero() && rollInput->IsZero()))
        {
            glm::vec3 rotationDelta(pitchInput->GetDelta(), yawInput->GetDelta(), rollInput->GetDelta());
            rotationDelta *= rotationSpeed * Engine::TimeModule::GetDeltaTime();
            rotationDelta = glm::radians(rotationDelta);
            Engine::Objects::RotateInOrientation(GetGameObject(), rotationDelta);
        }
    }

    size_t PlayerController::GetDefaultPriority() const
    {
        return priority;
    }

    void PlayerController::ClearEvents()
    {
        xInput = nullptr;
        yInput = nullptr;
        zInput = nullptr;
        pitchInput = nullptr;
        yawInput = nullptr;
        rollInput = nullptr;
    }
}