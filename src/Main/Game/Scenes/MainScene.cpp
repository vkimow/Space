#include "Game/Scenes/MainScene.h"

#include <numbers>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include "Game/Menus/MenusHeader.h"
#include "Shaders/ShaderCreator.h"

namespace Main::Game
{
    MainScene::MainScene(const std::string &name, Engine::Window *const window, Engine::Engine *const engine)
        : Scene(name, window, engine->GetTime(), engine->GetUI(), engine->GetInput(), engine->GetGraphics())
    {
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

        Shaders::InitializeShaders(GetGraphics());
        GetGraphics()->GetContainer()->AddMesh("Cube", vertices, indices, sizeof(vertices) / sizeof(vertices[0]), sizeof(indices) / sizeof(indices[0]));
        GetGraphics()->GetContainer()->AddLine("Forward", glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 15.0f));
        GetGraphics()->GetContainer()->AddLine("Up", glm::vec3(0.0f), glm::vec3(0.0f, 15.0f, 0.0f));
        GetGraphics()->GetContainer()->AddLine("Right", glm::vec3(0.0f), glm::vec3(15.0f, 0.0f, 0.0f));

        auto cube = CreateGameObject("Cube_1");
        Engine::Scripts::RenderScript* script = cube->EmplaceScript<Engine::Scripts::RenderScript>(GetGraphics()->GetRenderManager());
        script->EmplaceRenderUnit("MainShader", "Cube");
        script->EmplaceRenderUnit("MainShader", "Forward");
        script->EmplaceRenderUnit("MainShader", "Up");
        script->EmplaceRenderUnit("MainShader", "Right");

        CopyGameObject("Cube_2", *cube);
        CopyGameObject("Cube_3", *cube);
        CopyGameObject("Cube_4", *cube);
        GetGameObject("Cube_1")->GetTransform().SetPosition(5.0f, 0.0f, 5.0f);
        GetGameObject("Cube_2")->GetTransform().SetPosition(-5.0f, 0.0f, -5.0f);
        GetGameObject("Cube_3")->GetTransform().SetPosition(5.0f, 0.0f, -5.0f);
        GetGameObject("Cube_4")->GetTransform().SetPosition(-5.0f, 0.0f, 5.0f);
        GetGameObject("Cube_1")->GetTransform().SetRotationInDegrees(30.0f, 0.0f, 0.0f);
        GetGameObject("Cube_2")->GetTransform().SetRotationInDegrees(-30.0f, 0.0f, 0.0f);
        GetGameObject("Cube_3")->GetTransform().SetRotationInDegrees(0.0f, 0.0f, -30.0f);
        GetGameObject("Cube_4")->GetTransform().SetRotationInDegrees(0.0f, 0.0f, 30.0f);

        auto player = CreateGameObject("Player");
        Engine::Objects::SetPosition(player, 0.0f, 30.0f, 0.0f);
        Engine::Objects::SetRotationInDegrees(player, 90.0f, -90.0f, 0.0f);

        ///*
        auto scheme = GetInput()->GetScheme();
        auto movementInput = scheme->CreateVectorPressable(GLFW_KEY_D, GLFW_KEY_A, GLFW_KEY_W, GLFW_KEY_S);
        auto verticalInput = scheme->CreateDeltaPressable(GLFW_KEY_LEFT_SHIFT, GLFW_KEY_LEFT_CONTROL);
        auto mouseInput = scheme->GetMouse()->GetDeltaPositionInput();
        auto rollInput = scheme->CreateDeltaPressable(GLFW_KEY_Q, GLFW_KEY_E);
        player->EmplaceScript<Engine::Scripts::PlayerController>(movementInput->GetDeltaX(), verticalInput, movementInput->GetDeltaY(), mouseInput->GetDeltaY(), mouseInput->GetDeltaX(), rollInput, 10.0f, 100.0f);
        //*/

        auto projection = Engine::Graphics::Projection(90, window->GetResolution());
        auto camera = GetGraphics()->GetCameraManager()->AddCamera("Player Camera", projection);
        player->EmplaceScript<Engine::Scripts::CameraScript>(camera);
        GetGraphics()->GetRenderManager()->GetPool().SetCamera(camera);

        GetUI()->GetEditorManager()->SetActive(true);
        GetUI()->GetEditorManager()->SetTarget(GetGameObject("Cube_1"));
        GetUI()->GetMenuManager()->GetContainer().Get<Engine::UI::GameObjectsMenu>()->SetScene(this);
        GetUI()->GetMenuManager()->GetContainer().Get<Engine::UI::GameObjectsMenu>()->SetActive(true);
        GetUI()->GetMenuManager()->GetContainer().Get<GameModeMenu>()->SetActive(true);
    }

    MainScene::~MainScene()
    {}

    void MainScene::Update()
    {
        Engine::Objects::RotateInOrientation(GetGameObject("Cube_1"), 0.0f, Engine::TimeModule::GetDeltaTime(), 0.0f);
        Engine::Objects::RotateInOrientation(GetGameObject("Cube_2"), 0.0f, Engine::TimeModule::GetDeltaTime(), 0.0f);
        Engine::Objects::RotateInOrientation(GetGameObject("Cube_3"), 0.0f, Engine::TimeModule::GetDeltaTime(), 0.0f);
        Engine::Objects::RotateInOrientation(GetGameObject("Cube_4"), 0.0f, Engine::TimeModule::GetDeltaTime(), 0.0f);

        UpdateGameObject("Cube_1");
        UpdateGameObject("Cube_2");
        UpdateGameObject("Cube_3");
        UpdateGameObject("Cube_4");

        UpdateGameObject("Player");
    }

    void MainScene::Render()
    {}
}