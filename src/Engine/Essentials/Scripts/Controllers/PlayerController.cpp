#pragma once
#include "Engine/Essentials/Scripts/Controllers/PlayerController.h"
#include "Engine/Objects/GameObjectTools.h"
#include "Engine/Main/Modules/TimeModule.h"

namespace Engine::Scripts
{
    PlayerController::PlayerController(Objects::GameObject *object,
        Input::Delta *xInput, Input::Delta *yInput, Input::Delta *zInput,
        Input::Delta *pitchInput, Input::Delta *yawInput, Input::Delta *rollInput,
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

    Tools::Interfaces::IClonable *PlayerController::Clone()
    {
        return new PlayerController(*this);
    }

    void PlayerController::UpdateInner()
    {
        if (!(xInput->IsZero() && yInput->IsZero() && zInput->IsZero()))
        {
            glm::vec3 moveDelta(xInput->GetDelta(), yInput->GetDelta(), -zInput->GetDelta());
            moveDelta *= movementSpeed * TimeModule::GetDeltaTime();
            Objects::MoveInOrientation(GetGameObject(), moveDelta);
            auto newPos = GetGameObject()->GetTransform().GetPosition();
        }

        if (!(pitchInput->IsZero() && yawInput->IsZero() && rollInput->IsZero()))
        {
            glm::vec3 rotationDelta(pitchInput->GetDelta(), -yawInput->GetDelta(), -rollInput->GetDelta());
            rotationDelta *= rotationSpeed * TimeModule::GetDeltaTime();
            rotationDelta = glm::radians(rotationDelta);
            Objects::RotateInOrientation(GetGameObject(), rotationDelta); 
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