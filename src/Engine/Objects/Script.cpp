#include "Engine/Objects/Script.h"

#include "Engine/Objects/GameObject.h"

namespace Engine::Objects
{
    Script::Script()
        : object(nullptr)
    {}

    Script::Script(GameObject *object)
        : object(object)
    {}

    Script::Script(const Script &rhs)
        : object(rhs.object)
    {}

    Script::Script(Script &&rhs) noexcept
        : object(rhs.object)
    {
        rhs.object = nullptr;
    }

    Script &Script::operator=(const Script &rhs)
    {
        object = rhs.object;
        return *this;
    }

    Script &Script::operator=(Script &&rhs) noexcept
    {
        object = rhs.object;
        rhs.object = nullptr;
        return *this;
    }

    void Script::Update()
    {
        if (!object)
        {
            return;
        }

        UpdateInner();
    }

    GameObject *const Script::GetGameObject() const
    {
        return object;
    }
}