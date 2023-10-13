#include "Engine/Main/Modules/GraphicsModule.h"

namespace Engine
{
    GraphicsModule::GraphicsModule(GLFWwindow *const window)
        : window(window)
    {}

    void GraphicsModule::StartUpdate()
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void GraphicsModule::EndUpdate()
    {
        glUseProgram(0);
        glfwSwapBuffers(window);
    }
}