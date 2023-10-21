#include "Engine/Main/Modules/GraphicsModule.h"

namespace Engine
{
    GraphicsModule::GraphicsModule(GLFWwindow *const window)
        : window(window)
        , container(new Graphics::Container())
        , cameraManager(new Graphics::CameraManager())
        , renderManager(new Graphics::RenderManager(container))
    {}

    GraphicsModule::~GraphicsModule()
    {
        delete renderManager;
        delete cameraManager;
        delete container;
    }

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

    Graphics::RenderManager *const GraphicsModule::GetRenderManager()
    {
        return renderManager;
    }

    Graphics::CameraManager *const  GraphicsModule::GetCameraManager()
    {
        return cameraManager;
    }

    Graphics::Container *const GraphicsModule::GetContainer()
    {
        return container;
    }
}