#pragma once

namespace Engine::Graphics
{
    class IRendable
    {
    public:
        virtual void StartRender() = 0;
        virtual void Render() = 0;
        virtual void EndRender() = 0;
    };
}