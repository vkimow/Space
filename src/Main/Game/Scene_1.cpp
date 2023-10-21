#include "Main/Game/Scene_1.h"
#include "Main/Game/Configs/CmakeConfig.h"
#include "Main/Scripts/ScriptsHeader.h"

#include <glm/gtc/type_ptr.hpp>
#include <numbers>
#include <glm/gtx/matrix_decompose.hpp>

glm::vec3 rotateVector(glm::quat q, glm::vec3 v)
{
    glm::vec3 t = glm::cross(glm::vec3(q.x, q.y, q.z), v);
    t *= 2;
    auto result = v + q.w * t + glm::cross(glm::vec3(q.x, q.y, q.z), t);
    return result;
}


namespace Game
{
    Scene_1::Scene_1(const std::string &name, Engine::Window *const window, Engine::Modules *const modules)
        : Scene(name, window, modules)
    {
        auto &input = modules->GetInput();
        auto scheme = input.GetScheme();

        std::string vertexPath = CmakeConfig::ShadersRelativePath + "/shader.vert";
        std::string fragmentPath = CmakeConfig::ShadersRelativePath + "/shader.frag";

        // Vertices of a cube
        float vertices[] = {
            -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, // 0
             1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // 1
             1.0f,  1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, // 2
            -1.0f,  1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, // 3
            -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f, // 4
             1.0f, -1.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, 0.0f, // 5
             1.0f,  1.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, 1.0f, // 6
            -1.0f,  1.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 1.0f  // 7
        };

        unsigned int indices[] = {
            0, 1, 2, // front face
            2, 3, 0, // front face
            1, 5, 6, // right face
            6, 2, 1, // right face
            5, 4, 7, // back face
            7, 6, 5, // back face
            4, 0, 3, // left face
            3, 7, 4, // left face
            3, 2, 6, // top face
            6, 7, 3, // top face
            4, 5, 1, // bottom face
            1, 0, 4  // bottom face
        };

        GetModules()->GetGraphics().GetContainer().AddShader("MainShader", vertexPath, fragmentPath);
        GetModules()->GetGraphics().GetContainer().AddMesh("Cube", vertices, indices, sizeof(vertices), sizeof(indices));

        auto cube = CreateGameObject("Cube");
        auto &transform = cube->GetTransform();
        transform.SetRotationInDegrees(30.0f, 0.0f, 0.0f);

        auto player = CreateGameObject("Player");
        auto movementInput = scheme->CreateVectorPressable(GLFW_KEY_D, GLFW_KEY_A, GLFW_KEY_W, GLFW_KEY_S);
        auto verticalInput = scheme->CreateDeltaPressable(GLFW_KEY_SPACE, GLFW_KEY_LEFT_CONTROL);
        auto mouseInput = scheme->GetMouse()->GetDeltaPositionInput();
        auto rollInput = scheme->CreateDeltaPressable(GLFW_KEY_Q, GLFW_KEY_E);
        player->EmplaceScript<Game::Scripts::PlayerController>(movementInput->GetDeltaX(), verticalInput, movementInput->GetDeltaY(), mouseInput->GetDeltaY(), mouseInput->GetDeltaX(), rollInput, 10.0f, 100.0f);

        auto projection = Engine::Graphics::Projection(90, window->GetResolution());
        auto camera = GetModules()->GetGraphics().GetCameraManager().AddCamera("Player Camera", projection);
        player->EmplaceScript<Game::Scripts::CameraScript>(camera);
    }

    Scene_1::~Scene_1()
    {}

    void Game::Scene_1::Update()
    {
        UpdateGameObject("Player");
    }

    void Scene_1::Render()
    {    
        auto shader = GetModules()->GetGraphics().GetContainer().GetShader("MainShader");
        shader->Use();
        auto player = GetGameObject("Player");
        auto camera = GetModules()->GetGraphics().GetCameraManager().GetMainCamera();
        auto mesh_1 = GetModules()->GetGraphics().GetContainer().GetMesh("Cube");
        //glm::mat4 projectionMatrix = camera->GetProjectionMatrix();
        //glm::mat4 viewMatrix = camera->GetViewProjectionMatrix();
        //glm::mat4 viewProjectionMatrix = camera->GetViewProjectionMatrix();
        glm::mat4 projectionMatrix = camera->GetProjectionMatrix();
        glm::mat4 viewMatrix = camera->GetViewMatrix();

        glUniformMatrix4fv(shader->GetProjectionUniform(), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
        glUniformMatrix4fv(shader->GetViewUniform(), 1, GL_FALSE, glm::value_ptr(viewMatrix));

        auto *cube = GetGameObject("Cube");
        auto &transform = cube->GetTransform();

        transform.SetRotationInDegrees(30.0f, 0.0f, 0.0f);
        transform.Rotate(0.0f, Engine::TimeModule::GetGlobalTime(), 0.0f);
        transform.SetPosition(3.0f, 0.0f, 0.0f);
        glm::mat4 transformMatrix = transform.GetTransformMatrix();
        glUniformMatrix4fv(shader->GetModelUniform(), 1, GL_FALSE, glm::value_ptr(transformMatrix));
        mesh_1->Render();

        transform.SetRotationInDegrees(30.0f, 0.0f, 0.0f);
        transform.RotateInOrientation(0.0f, Engine::TimeModule::GetGlobalTime(), 0.0f);
        transform.SetPosition(-3.0f, 0.0f, 0.0f);
        transformMatrix = transform.GetTransformMatrix();
        glUniformMatrix4fv(shader->GetModelUniform(), 1, GL_FALSE, glm::value_ptr(transformMatrix));
        mesh_1->Render();

        //transform.SetPosition(0.0f, 0.0f, 2.0f);
        //glUniformMatrix4fv(shader.GetModelUniform(), 1, GL_FALSE, glm::value_ptr(transform.GetTransformMatrix()));
        //mesh_1.RenderMesh();

        //transform.SetPosition(0.0f, 0.0f, -2.0f);
        //glUniformMatrix4fv(shader.GetModelUniform(), 1, GL_FALSE, glm::value_ptr(transform.GetTransformMatrix()));
        //mesh_1.RenderMesh();

        //transform.SetPosition(0.0f, 0.0f, 0.0f);
        //glUniformMatrix4fv(shader.GetModelUniform(), 1, GL_FALSE, glm::value_ptr(transform.GetTransformMatrix()));
        //mesh_1.RenderMesh();

        shader->Validate();
    }
}