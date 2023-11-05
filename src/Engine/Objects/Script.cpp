#include "Engine/Objects/Script.h"
#include "Engine/Objects/GameObject.h"

namespace Engine::Objects
{
    Script::Script()
        : isActive(true)
        , isEnabled(false)
        , object(nullptr)
    {}

    Script::Script(GameObject *object)
        : isActive(true)
        , isEnabled(false)
        , object(object)
    {}

    Script::Script(const Script &rhs)
        : isActive(rhs.isActive)
        , isEnabled(false)
        , object(rhs.object)
    {}

    Script::Script(Script &&rhs) noexcept
        : isActive(rhs.isActive)
        , isEnabled(false)
        , object(rhs.object)
    {
        rhs.object = nullptr;
    }

    Script &Script::operator=(const Script &rhs)
    {
        isActive = rhs.isActive;
        isEnabled = rhs.isEnabled;
        object = rhs.object;
        return *this;
    }

    Script &Script::operator=(Script &&rhs) noexcept
    {
        isActive = rhs.isActive;
        isEnabled = rhs.isEnabled;
        object = rhs.object;
        rhs.object = nullptr;
        return *this;
    }

    bool Script::IsActive() const
    {
        return isActive && object && object->IsActive();
    }

    void Script::SetActive(bool value)
    {
        isActive = value;

        if (isActive)
        {
            OnEnabled();
        }
        else
        {
            OnDisabled();
        }
    }

    void Script::OnEnabled()
    {
        if (!isEnabled && IsActive())
        {
            OnEnabledInner();
            isEnabled = true;
        }
    }

    void Script::OnDisabled()
    {
        if (isEnabled && !IsActive())
        {
            OnDisabledInner();
            isEnabled = false;
        }
    }

    void Script::Update()
    {
        UpdateInner();
    }

    GameObject *const Script::GetGameObject() const
    {
        return object;
    }

    Transform& Script::GetTransform()
    {
        return object->GetTransform();
    }

    const Transform &Script::GetTransform() const
    {
        return object->GetTransform();
    }

    void Script::SetGameObject(GameObject *value)
    {
        OnDisabled();
        object = value;
    }
}