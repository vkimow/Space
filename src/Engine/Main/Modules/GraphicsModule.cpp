#include "Engine/Main/Modules/GraphicsModule.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Engine/Graphics/GraphicsHeader.h"
#include "Engine/Window/Window.h"

namespace Engine
{
    GraphicsModule::GraphicsModule(Window *const window)
        : window(window->GetInnerWindow())
        , container(new Graphics::Container())
        , cameraManager(new Graphics::CameraManager())
        , lightManager(new Graphics::LightManager())
        , renderManager(new Graphics::RenderManager(container, cameraManager->GetMainCamera(), lightManager))
        , postProcessing(new Graphics::PostProcessingManager(window, container))
    {}

    GraphicsModule::~GraphicsModule()
    {
        delete postProcessing;
        delete renderManager;
        delete lightManager;
        delete cameraManager;
        delete container;
    }

    void GraphicsModule::StartRender()
    {
        cameraManager->Update();
        postProcessing->EnableRenderBuffer();
        glEnable(GL_DEPTH_TEST);
    }

    void GraphicsModule::Render()
    {
        renderManager->GetPool().RenderAll();
    }

    void GraphicsModule::EndRender()
    {
        glUseProgram(0);
        glfwSwapBuffers(window);
    }

    void GraphicsModule::PostProcessing()
    {
        glUseProgram(0);
        postProcessing->DisableRenderBuffer();
        glDisable(GL_DEPTH_TEST);
        postProcessing->PostProcess();
    }


    Graphics::PostProcessingManager *const GraphicsModule::GetPostProcessing()
    {
        return postProcessing;
    }

    Graphics::RenderManager *const GraphicsModule::GetRenderManager()
    {
        return renderManager;
    }

    Graphics::LightManager *const GraphicsModule::GetLightManager()
    {
        return lightManager;
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