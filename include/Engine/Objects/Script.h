#pragma once

#include "Engine/Tools/Interfaces/IClonable.h"

namespace Engine::Objects
{
    class GameObject;

    class Script : public Tools::Interfaces::IClonable
    {
        friend class GameObject;

    protected:
        Script();
        Script(GameObject* object);

        Script(const Script &rhs);
        Script(Script &&rhs) noexcept;

        Script &operator=(const Script &rhs);
        Script &operator=(Script &&rhs) noexcept;

    public:
        virtual ~Script() = default;

    private:
        void Update();

    protected:
        virtual void SetGameObject(GameObject *value);

    protected:
        virtual void UpdateInner() = 0;
        virtual size_t GetDefaultPriority() const = 0;

    public:
        GameObject *const GetGameObject() const;

    private:
        GameObject *object;
    };
}