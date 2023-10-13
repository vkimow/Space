#include "Scene.h"
#include "Scene_1.h"
#include "Configs/CmakeConfig.h"

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

        auto vertexPath = CmakeConfig::ShadersRelativePath + "/shader.vert";
        auto fragmentPath = CmakeConfig::ShadersRelativePath + "/shader.frag";
        shader.CreateFromFiles(std::move(vertexPath), std::move(fragmentPath));

        glCreateVertexArrays(1, &VertexArrayObject);
    }

    Scene_1::~Scene_1()
    {
        glDeleteVertexArrays(1, &VertexArrayObject);
    }

    void Game::Scene_1::Update()
    {
    }

    void Scene_1::Render()
    {

        shader.Use();
        glBindVertexArray(VertexArrayObject);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        shader.Validate();
    }
}