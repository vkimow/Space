#pragma once

namespace Engine::Objects
{
    class Script
    {
        friend class GameObject;

    protected:
        Script();
        Script(const Script &rhs);
        Script(Script &&rhs) noexcept;

        Script &operator=(const Script &rhs);
        Script &operator=(Script &&rhs) noexcept;

    private:
        virtual ~Script();

    private:
        virtual Script *Clone() noexcept = 0;

    private:
        virtual void Update() = 0;

    };
}