#pragma once

namespace Engine::Graphics
{
    class Material
    {
        friend class Container;

    private:
        Material();
        Material(const Material &rhs) = delete;
        Material(Material &&rhs) = delete;
        Material &operator=(const Material &rhs) = delete;
        Material &operator=(Material &&rhs) = delete;
        ~Material();
    };
}