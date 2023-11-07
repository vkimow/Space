#pragma once

struct GLFWwindow;
namespace Engine::Graphics
{
    class PostProcessingManager;
    class RenderManager;
    class LightManager;
    class CameraManager;
    class Container;
}

namespace Engine
{
    class Window;
    class GraphicsModule
    {
        friend class Engine;

    private:
        GraphicsModule(Window *const window);

        GraphicsModule() = delete;
        GraphicsModule(const GraphicsModule &rhs) = delete;
        GraphicsModule(GLFWwindow &&rhs) = delete;
        GraphicsModule &operator=(const GraphicsModule &rhs) = delete;
        GraphicsModule &operator=(GraphicsModule &&rhs) = delete;

        ~GraphicsModule();

    private:
        void StartRender();
        void Render();
        void EndRender();
        void PostProcessing();

    public:
        Graphics::PostProcessingManager *const GetPostProcessing();
        Graphics::RenderManager *const GetRenderManager();
        Graphics::LightManager *const GetLightManager();
        Graphics::CameraManager *const GetCameraManager();
        Graphics::Container *const GetContainer();

    private:
        GLFWwindow *const window;
        Graphics::Container *const container;
        Graphics::CameraManager *const cameraManager;
        Graphics::LightManager *const lightManager;
        Graphics::RenderManager *const renderManager;
        Graphics::PostProcessingManager *const postProcessing;
    };
}