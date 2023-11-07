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

        GetGraphics()->GetContainer()->AddMesh("Sphere", Engine::Graphics::Sphere());
        GetGraphics()->GetContainer()->AddMesh("Plane", Engine::Graphics::Plane());
        GetGraphics()->GetContainer()->AddLine("Forward", glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 15.0f));
        GetGraphics()->GetContainer()->AddLine("Up", glm::vec3(0.0f), glm::vec3(0.0f, 15.0f, 0.0f));
        GetGraphics()->GetContainer()->AddLine("Right", glm::vec3(0.0f), glm::vec3(15.0f, 0.0f, 0.0f));
        GetGraphics()->GetContainer()->AddMaterial<Engine::Graphics::PBRMaterial>("Red_GLOW", 100.0f, 60.0f, 30.0f, 1.0f);
        GetGraphics()->GetContainer()->AddMaterial<Engine::Graphics::PBRMaterial>("Red", 1.0f, 0.0f, 0.0f, 1.0f);
        GetGraphics()->GetContainer()->AddMaterial<Engine::Graphics::PBRMaterial>("Green", 0.0f, 1.0f, 0.0f, 1.0f);
        GetGraphics()->GetContainer()->AddMaterial<Engine::Graphics::PBRMaterial>("Blue", 0.0f, 0.0f, 1.0f, 1.0f);
        GetGraphics()->GetContainer()->AddMaterial<Engine::Graphics::PBRMaterial>("Orange", 3.0f, 2.00f, 0.0f, 1.0f);

        Engine::Scripts::RenderScript *renderScript = nullptr;
        Space::StarScript *starScript = nullptr;
        Space::CelestialBodyScript *celestialBodyScript = nullptr;
        auto sun = CreateGameObject("Sun_1");
        renderScript = sun->EmplaceScript<Engine::Scripts::RenderScript>(GetGraphics()->GetRenderManager());
        renderScript->EmplaceRenderUnit("MainShader", "Sphere", "Red_GLOW");
        starScript = sun->EmplaceScript<Space::StarScript>(space, GetGraphics());
        celestialBodyScript = sun->GetScript<Space::CelestialBodyScript>();
        celestialBodyScript->SetMass(1000000000.0f);
        celestialBodyScript->SetRadius(20.0f);
        celestialBodyScript->SetVelocity(glm::vec3(0.0, 0.0f, 0.0f));

        auto planet = CreateGameObject("Planet_1");
        renderScript = planet->EmplaceScript<Engine::Scripts::RenderScript>(GetGraphics()->GetRenderManager());
        renderScript->EmplaceRenderUnit("MainShader", "Sphere", "Green");
        celestialBodyScript = planet->EmplaceScript<Space::CelestialBodyScript>(space, GetGraphics());
        celestialBodyScript->SetMass(1000000.0f);
        celestialBodyScript->SetVelocity(glm::vec3(0.0, 0.0f, 7.7f));
        celestialBodyScript->SetRadius(5.0f);

        //CopyGameObject("Planet_2", *planet);
        //CopyGameObject("Planet_3", *planet);
        //CopyGameObject("Planet_4", *planet);

        GetGameObject("Planet_1")->GetTransform().SetPosition(0.0f, 0.0f, 150.0f);
        celestialBodyScript = GetGameObject("Planet_1")->GetScript<Space::CelestialBodyScript>();
        celestialBodyScript->SetVelocity(glm::vec3(30.0f, 0.0f, 0.0f));

        //GetGameObject("Planet_2")->GetTransform().SetPosition(150.0f, 0.0f, 0.0f);
        //celestialBodyScript = GetGameObject("Planet_2")->GetScript<Space::CelestialBodyScript>();
        //celestialBodyScript->SetVelocity(glm::vec3(0.0f, 0.0f, 500.0f));
        //GetGameObject("Planet_3")->GetTransform().SetPosition(-100.0f, 0.0f, 0.0f);
        //celestialBodyScript = GetGameObject("Planet_3")->GetScript<Space::CelestialBodyScript>();
        //celestialBodyScript->SetVelocity(glm::vec3(0.0f, 0.0f, -750.0f));
        //GetGameObject("Planet_4")->GetTransform().SetPosition(0.0f, 0.0f, -130);
        //celestialBodyScript = GetGameObject("Planet_4")->GetScript<Space::CelestialBodyScript>();
        //celestialBodyScript->SetVelocity(glm::vec3(-950.0f, 0.0f, 0.0f));

        auto plane = CreateGameObject("Plane_1");
        renderScript = plane->EmplaceScript<Engine::Scripts::RenderScript>(GetGraphics()->GetRenderManager());
        renderScript->EmplaceRenderUnit("MainShader", "Plane");
        Engine::Objects::SetPosition(plane, 0.0f, -2.0f, 0.0f);
        Engine::Objects::SetScale(plane, 100.0f, 100.0f, 100.0f);

        auto player = CreateGameObject("Player");
        Engine::Objects::SetPosition(player, 0.0f, 300.0f, 15.0f);
        Engine::Objects::SetRotationInDegrees(player, -90.0f, 0.0f, 0.0f);

        auto scheme = GetInput()->GetScheme();
        auto movementInput = scheme->CreateVectorPressable(GLFW_KEY_D, GLFW_KEY_A, GLFW_KEY_W, GLFW_KEY_S);
        auto verticalInput = scheme->CreateDeltaPressable(GLFW_KEY_SPACE, GLFW_KEY_LEFT_CONTROL);
        auto mouseInput = scheme->GetMouse()->GetDeltaPositionInput();
        auto rollInput = scheme->CreateDeltaPressable(GLFW_KEY_Q, GLFW_KEY_E);
        player->EmplaceScript<Engine::Scripts::PlayerController>(movementInput->GetDeltaX(), verticalInput, movementInput->GetDeltaY(), mouseInput->GetDeltaY(), mouseInput->GetDeltaX(), rollInput, 10.0f, 100.0f);

        auto projection = Engine::Graphics::Projection(window, 90, 0.01f, 100000.0f);
        auto vCamera = GetGraphics()->GetCameraManager()->AddVirtualCamera<Engine::Graphics::VirtualCamera>("Player Camera", projection);
        player->EmplaceScript<Engine::Scripts::CameraScript>(vCamera);

        auto ambient = GetGraphics()->GetLightManager()->GetContainer().InitializeAmbientLight();
        ambient->GetLight().SetIntensity(0.2f);
    }

    MainScene::~MainScene()
    {}

    void MainScene::Update()
    {

    }

    void MainScene::Render()
    {}
}