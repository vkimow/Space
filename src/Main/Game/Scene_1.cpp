#include "Engine/Objects//Scene.h"
#include "Scene_1.h"
#include "Configs/CmakeConfig.h"
#include <glm/gtc/type_ptr.hpp>
#include <numbers>

namespace Game
{
    Scene_1::Scene_1(const std::string &name, Engine::Window *const window, Engine::Modules *const modules)
        : Scene(name, window, modules)
    {
        auto &input = modules->GetInput();
        auto scheme = input.GetScheme();


        movementInput = scheme->CreateVectorPressable(GLFW_KEY_D, GLFW_KEY_A, GLFW_KEY_W, GLFW_KEY_S);
        mouseInput = scheme->GetMouse();

        camera = Engine::Graphics::Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 1.0f, 0.5f, movementInput, mouseInput->GetDeltaPositionInput());
        projection = Engine::Graphics::Projection(window, 90.0f);

        auto vertexPath = CmakeConfig::ShadersRelativePath + "/shader.vert";
        auto fragmentPath = CmakeConfig::ShadersRelativePath + "/shader.frag";
        shader.CreateFromFiles(std::move(vertexPath), std::move(fragmentPath));

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


        mesh_1.CreateMesh(vertices, indices, sizeof(vertices), sizeof(indices));
        mesh_2.CreateMesh(vertices, indices, sizeof(vertices), sizeof(indices));
        mesh_3.CreateMesh(vertices, indices, sizeof(vertices), sizeof(indices));
        mesh_4.CreateMesh(vertices, indices, sizeof(vertices), sizeof(indices));
        mesh_5.CreateMesh(vertices, indices, sizeof(vertices), sizeof(indices));

        CreateGameObject("Cube");
    }

    Scene_1::~Scene_1()
    {}

    void Game::Scene_1::Update()
    {
        camera.Update();
    }

    void Scene_1::Render()
    {
        shader.Use();
        glm::mat4 projectionMatrix = projection.GetProjectionMatrix();
        glm::mat4 viewMatrix = camera.GetViewMatrix();
        //glm::mat4 viewMatrix(1.0f);

        glUniformMatrix4fv(shader.GetProjectionUniform(), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
        glUniformMatrix4fv(shader.GetViewUniform(), 1, GL_FALSE, glm::value_ptr(viewMatrix));

        float time = Engine::TimeModule::GetGlobalTime();
        float angle = glm::cos(time) * glm::pi<float>();
        float angle2 = glm::sin(time) * glm::pi<float>();
        float angle3 = -glm::cos(time) * glm::pi<float>();

        auto *cube = GetGameObject("Cube");
        auto &transform = cube->GetTransform();
        transform.SetOrientation(angle, angle2, angle3);
        auto anglesResult = transform.GetEurlerOrientation();
        LOG_DEBUG("Angles:{}.{}.{}", anglesResult.x, anglesResult.y, anglesResult.z);

        transform.SetPosition(2.0f, 0.0f, 0.0f);
        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
        model = glm::rotate(model, angle, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, angle2, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, angle3, glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 transformMatrix = transform.GetTransformMatrix();

        glUniformMatrix4fv(shader.GetModelUniform(), 1, GL_FALSE, glm::value_ptr(transformMatrix));
        mesh_1.RenderMesh();

        transform.SetPosition(-2.0f, 0.0f, 0.0f);
        glUniformMatrix4fv(shader.GetModelUniform(), 1, GL_FALSE, glm::value_ptr(transform.GetTransformMatrix()));
        mesh_1.RenderMesh();

        transform.SetPosition(0.0f, 0.0f, 2.0f);
        glUniformMatrix4fv(shader.GetModelUniform(), 1, GL_FALSE, glm::value_ptr(transform.GetTransformMatrix()));
        mesh_1.RenderMesh();

        transform.SetPosition(0.0f, 0.0f, -2.0f);
        glUniformMatrix4fv(shader.GetModelUniform(), 1, GL_FALSE, glm::value_ptr(transform.GetTransformMatrix()));
        mesh_1.RenderMesh();

        transform.SetPosition(0.0f, 0.0f, 0.0f);
        glUniformMatrix4fv(shader.GetModelUniform(), 1, GL_FALSE, glm::value_ptr(transform.GetTransformMatrix()));
        mesh_1.RenderMesh();

        shader.Validate();
    }
}