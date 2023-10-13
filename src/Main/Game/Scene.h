#pragma once

#include <string>
#include "Engine/Main/EngineHeader.h"

namespace Game
{
    class Scene
    {
    public:
        Scene(const std::string& name, Engine::Modules* const modules);
        virtual ~Scene() = default;

    public:
        virtual void Update() = 0;
        virtual void Render() = 0;

    protected:
        size_t id;
        std::string name;
        Engine::Modules *const modules;

    private:
        static size_t idCounter;
    };
}