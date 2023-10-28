#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Engine/Graphics/Camera/CameraManager.h"
#include "Engine/Graphics/Render/RenderManager.h"
#include "Engine/Graphics/Elements/Container.h"

namespace Engine
{
    class GraphicsModule
    {
        friend class Engine;

    private:
        GraphicsModule(GLFWwindow *const window);

        GraphicsModule() = delete;
        GraphicsModule(const GraphicsModule &rhs) = delete;
        GraphicsModule(GLFWwindow &&rhs) = delete;
        GraphicsModule &operator=(const GraphicsModule &rhs) = delete;
        GraphicsModule &operator=(GraphicsModule &&rhs) = delete;

        ~GraphicsModule();

    private:
        void StartUpdate();
        void EndUpdate();

    public:
        Graphics::RenderManager *const GetRenderManager();
        Graphics::CameraManager *const GetCameraManager();
        Graphics::Container *const GetContainer();

    private:
        GLFWwindow *const window;
        Graphics::Container *const container;
        Graphics::CameraManager *const cameraManager;
        Graphics::RenderManager *const renderManager;
    };
}