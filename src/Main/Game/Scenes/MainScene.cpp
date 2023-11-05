#include "Game/Scenes/MainScene.h"

#include <numbers>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include "Game/Menus/MenusHeader.h"
#include "Shaders/ShaderCreator.h"

namespace Main::Game
{
    MainScene::MainScene(const std::string &name, Engine::Window *const window, Engine::Engine *const engine, Space::SpaceManager *const space)
        : Scene(name, window, engine->GetTime(), engine->GetUI(), engine->GetInput(), engine->GetGraphics())
        , space(space)
    {
       
        Shaders::InitializeShaders(GetGraphics());

        GetGraphics()->GetContainer()->AddMesh("Cube", Engine::Graphics::Cube());
        GetGraphics()->GetContainer()->AddLine("Forward", glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 15.0f));
        GetGraphics()->GetContainer()->AddLine("Up", glm::vec3(0.0f), glm::vec3(0.0f, 15.0f, 0.0f));
        GetGraphics()->GetContainer()->AddLine("Right", glm::vec3(0.0f), glm::vec3(15.0f, 0.0f, 0.0f));


        auto cube = CreateGameObject("Cube_1");
        Engine::Scripts::RenderScript* renderScript = cube->EmplaceScript<Engine::Scripts::RenderScript>(GetGraphics()->GetRenderManager());
        renderScript->EmplaceRenderUnit("MainShader", "Cube");
        Space::CelestialBodyScript *celestialBodyScript = cube->EmplaceScript<Space::CelestialBodyScript>(space, GetGraphics());
        celestialBodyScript->SetMass(200.0f);
        celestialBodyScript->SetVelocity(glm::vec3(0.0, 0.0f, 100.0f));

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
        Engine::Objects::SetPosition(player, 0.0f, 100.0f, 0.0f);
        Engine::Objects::SetRotationInDegrees(player, 90.0f, -90.0f, 0.0f);

        /*
        auto scheme = GetInput()->GetScheme();
        auto movementInput = scheme->CreateVectorPressable(GLFW_KEY_D, GLFW_KEY_A, GLFW_KEY_W, GLFW_KEY_S);
        auto verticalInput = scheme->CreateDeltaPressable(GLFW_KEY_LEFT_SHIFT, GLFW_KEY_LEFT_CONTROL);
        auto mouseInput = scheme->GetMouse()->GetDeltaPositionInput();
        auto rollInput = scheme->CreateDeltaPressable(GLFW_KEY_Q, GLFW_KEY_E);
        player->EmplaceScript<Engine::Scripts::PlayerController>(movementInput->GetDeltaX(), verticalInput, movementInput->GetDeltaY(), mouseInput->GetDeltaY(), mouseInput->GetDeltaX(), rollInput, 10.0f, 100.0f);
        */

        auto projection = Engine::Graphics::Projection(90, window->GetResolution(), 0.01f, 100000.0f);
        auto camera = GetGraphics()->GetCameraManager()->AddVirtualCamera<Engine::Graphics::VirtualCamera>("Player Camera", projection);
        player->EmplaceScript<Engine::Scripts::CameraScript>(camera);
    }

    MainScene::~MainScene()
    {}

    void MainScene::Update()
    {

    }

    void MainScene::Render()
    {}
}