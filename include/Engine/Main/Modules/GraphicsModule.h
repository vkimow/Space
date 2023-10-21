#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Engine/Graphics/CameraManager.h"
#include "Engine/Graphics/RenderPool.h"
#include "Engine/Graphics/Container.h"

namespace Game
{
    class App;
}

namespace Engine
{
    class GraphicsModule
    {
        friend class Game::App;
        friend class Modules;

    private:
        GraphicsModule(GLFWwindow *const window);

        GraphicsModule() = delete;
        GraphicsModule(const GraphicsModule &rhs) = delete;
        GraphicsModule(GLFWwindow &&rhs) = delete;
        GraphicsModule& operator=(const GraphicsModule &rhs) = delete;
        GraphicsModule &operator=(GraphicsModule &&rhs) = delete;

        ~GraphicsModule();

    private:
        void StartUpdate();
        void EndUpdate();

    public:
        Graphics::CameraManager& GetCameraManager();
        Graphics::RenderPool& GetRenderPool();
        Graphics::Container &GetContainer();

    private:
        GLFWwindow *const window;
        Graphics::CameraManager cameraManager;
        Graphics::RenderPool renderPool;
        Graphics::Container container;
    };
}