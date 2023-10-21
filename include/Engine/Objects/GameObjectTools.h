#pragma once

#include "Engine/Objects/GameObject.h"

namespace Engine::Objects
{
    template<typename... Args>
    void SetPosition(GameObject &object, Args&&... args)
    {
        object.GetTransform().SetPosition(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void SetPosition(GameObject *const object, Args&&... args)
    {
        object->GetTransform().SetPosition(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void SetPositionInOrientation(GameObject &object, Args&&... args)
    {
        object.GetTransform().SetPositionInOrientation(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void SetPositionInOrientation(GameObject *const object, Args&&... args)
    {
        object->GetTransform().SetPositionInOrientation(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void Move(GameObject &object, Args&&... args)
    {
        object.GetTransform().Move(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void Move(GameObject *const object, Args&&... args)
    {
        object->GetTransform().Move(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void MoveInOrientation(GameObject &object, Args&&... args)
    {
        object.GetTransform().MoveInOrientation(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void MoveInOrientation(GameObject *const object, Args&&... args)
    {
        object->GetTransform().MoveInOrientation(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void SetScale(GameObject &object, Args&&... args)
    {
        object.GetTransform().SetScale(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void SetScale(GameObject *const object, Args&&... args)
    {
        object->GetTransform().SetScale(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void Scale(GameObject &object, Args&&... args)
    {
        object.GetTransform().Scale(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void Scale(GameObject *const object, Args&&... args)
    {
        object->GetTransform().Scale(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void SetRotation(GameObject &object, Args&&... args)
    {
        object.GetTransform().SetRotation(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void SetRotation(GameObject *const object, Args&&... args)
    {
        object->GetTransform().SetRotation(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void SetRotationInDegrees(GameObject &object, Args&&... args)
    {
        object.GetTransform().SetRotationInDegrees(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void SetRotationInDegrees(GameObject *const object, Args&&... args)
    {
        object->GetTransform().SetRotationInDegrees(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void Rotate(GameObject &object, Args&&... args)
    {
        object.GetTransform().Rotate(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void Rotate(GameObject *const object, Args&&... args)
    {
        object->GetTransform().Rotate(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void RotateInDegrees(GameObject &object, Args&&... args)
    {
        object.GetTransform().RotateInDegrees(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void RotateInDegrees(GameObject *const object, Args&&... args)
    {
        object->GetTransform().RotateInDegrees(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void RotateInOrientation(GameObject &object, Args&&... args)
    {
        object.GetTransform().RotateInOrientation(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void RotateInOrientation(GameObject *const object, Args&&... args)
    {
        object->GetTransform().RotateInOrientation(std::forward<Args>(args)...);
    }
}