#include "App.h"

namespace Game
{
    App::App()
        : isActive(false)
        , window(new Engine::Window("Space", 1280, 720))
        , engine(new Engine::Engine(window))
    {
        scene = new Scene_1("First Scene", window, engine);
    }

    App::~App()
    {
        delete scene;
        delete engine;
        delete window;
    }

    void App::Start()
    {
        isActive = true;
        while (!ShouldExit())
        {
            engine->GetInput()->Update();
            engine->GetTime()->Update();

            scene->Update();

            engine->GetGraphics()->StartUpdate();
            engine->GetGraphics()->GetRenderManager()->GetPool().RenderAll();
            scene->Render();
            engine->GetGraphics()->EndUpdate();

            engine->GetInput()->LateUpdate();
        }
    }

    void App::Quit()
    {
        isActive = false;
    }

    bool App::ShouldExit()
    {
        return glfwWindowShouldClose(window->GetInnerWindow()) || !isActive;
    }
}