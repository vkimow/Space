#pragma once

namespace Engine::Input
{

    class  Element
    {
        friend class InputModule;
        friend class Scheme;

    protected:
        Element();
        virtual ~Element();

    public:

    public:
        void SetActive(bool value);
        bool IsActive() const { return isActive; }

    private:
        bool isActive;
    };
}
