#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace Engine
{
    class GraphicsModule
    {
    public:
        GraphicsModule(GLFWwindow *const window);

    public:
        void StartUpdate();

        void EndUpdate();

    private:
        GLFWwindow *const window;
    };
}