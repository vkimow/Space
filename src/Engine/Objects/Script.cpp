#include "Engine/Objects/Script.h"
#include "Engine/Objects/GameObject.h"

namespace Engine::Objects
{
    Script::Script()
        : isActive(true)
        , object(nullptr)
    {}

    Script::Script(GameObject *object)
        : isActive(true)
        , object(object)
    {}

    Script::Script(const Script &rhs)
        : isActive(true)
        , object(rhs.object)
    {}

    Script::Script(Script &&rhs) noexcept
        : isActive(true)
        , object(rhs.object)
    {
        rhs.object = nullptr;
    }

    Script &Script::operator=(const Script &rhs)
    {
        isActive = rhs.isActive;
        object = rhs.object;
        return *this;
    }

    Script &Script::operator=(Script &&rhs) noexcept
    {
        isActive = rhs.isActive;
        object = rhs.object;
        rhs.object = nullptr;
        return *this;
    }

    bool Script::IsActive() const
    {
        return isActive && object;
    }

    void Script::SetActive(bool value)
    {
        isActive = value;
    }

    void Script::Update()
    {
        UpdateInner();
    }

    GameObject *const Script::GetGameObject() const
    {
        return object;
    }

    void Script::SetGameObject(GameObject *value)
    {
        object = value;
    }
}