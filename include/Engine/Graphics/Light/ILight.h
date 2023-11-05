#pragma once 

namespace Engine::Graphics
{
    class Shader;

    class ILight
    {
    public:
        virtual void Use(Shader *shader) = 0;
        virtual void Disable(Shader *shader) = 0;

    public:
        virtual void SetActive(bool value) = 0;
        virtual bool IsActive() const = 0;
    };
}
