#pragma once

namespace Engine::Objects
{
    class GameObject;

    class Script
    {
        friend class GameObject;

    protected:
        Script();
        Script(GameObject* object);

        Script(const Script &rhs);
        Script(Script &&rhs) noexcept;

        Script &operator=(const Script &rhs);
        Script &operator=(Script &&rhs) noexcept;

        virtual ~Script() = default;

    private:
        void Update();

    protected:
        virtual Script *Clone() noexcept = 0;
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