#include "Scene.h"
#include "Scene_1.h"

namespace Game
{
    Scene_1::Scene_1(const std::string &name, Engine::Modules *const modules)
        : Scene(name, modules)
    {
        auto &input = modules->GetInput();
        auto scheme = input.GetScheme();

        f = scheme->CreatePressableKey(GLFW_KEY_F);
        leftButton = scheme->CreatePressableMouse(GLFW_MOUSE_BUTTON_LEFT);
        delta = scheme->CreateDeltaPressable(GLFW_KEY_Q, GLFW_KEY_E);
        vector = scheme->CreateVectorPressable(GLFW_KEY_D, GLFW_KEY_A, GLFW_KEY_W, GLFW_KEY_S);
        mouse = scheme->GetMouse();
    }

    void Game::Scene_1::Update()
    {
        if (f->IsPressed())
        {
            LOG_ERROR("FFFFFFFF@@@\n");
        }

        if (leftButton->IsPressed())
        {
            LOG_INFO("LEFT BUTTON!!!\n");
        }

        if (!delta->IsZero())
        {
            LOG_WARN("-----------DELTA = {}", delta->GetDelta());
        }

        if (!vector->IsZero())
        {
            LOG_CRITICAL(">>>>>>>>VECTOR X:{} Y:{}", vector->GetVector().x, vector->GetVector().y);
        }
    }
    void Scene_1::UpdateVisuals()
    {

    }
}