#include "Engine/Main/Modules/GraphicsModule.h"

namespace Engine
{
    GraphicsModule::GraphicsModule(GLFWwindow *const window)
        : window(window)
    {}

    void GraphicsModule::StartUpdate()
    {

    }

    void GraphicsModule::EndUpdate()
    {
        glfwSwapBuffers(window);
    }
}