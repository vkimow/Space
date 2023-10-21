#pragma once

namespace Engine::Graphics
{
    class Texture
    {
        friend class Container;

    private:
        Texture();
        Texture(const Texture &rhs) = delete;
        Texture(Texture &&rhs) = delete;
        Texture &operator=(const Texture &rhs) = delete;
        Texture &operator=(Texture &&rhs) = delete;
        ~Texture();
    };
}