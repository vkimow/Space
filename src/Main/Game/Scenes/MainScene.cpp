#include "Game/Scenes/MainScene.h"

#include <numbers>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include "Game/Menus/MenusHeader.h"
#include "Shaders/ShaderCreator.h"

#include "Game/GameManager.h"

namespace Main::Game
{
    MainScene::MainScene(const std::string &name, Engine::Window *const window, Engine::Engine *const engine, Space::SpaceManager *const space, GameManager *gameManager)
        : Scene(name, window, engine->GetTime(), engine->GetUI(), engine->GetInput(), engine->GetGraphics())
        , space(space)
        , gameManager(gameManager)
        , switchState(this, &MainScene::SwitchState)
        , changeGameMode(this, &MainScene::ChangeGameMode)
        , escape(nullptr)
        , currentState(false)
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
        GetGraphics()->GetContainer()->AddMaterial<Engine::Graphics::PBRMaterial>("Purple", 0.63f, 0.13f, 0.94f, 1.0f);
        GetGraphics()->GetContainer()->AddMaterial<Engine::Graphics::PBRMaterial>("Aqua", 0.2f, 1.0f, 1.0f, 1.0f);
        GetGraphics()->GetContainer()->AddMaterial<Engine::Graphics::PBRMaterial>("Pink", 1.0f, 0.5f, 0.92f, 1.0f);
        GetGraphics()->GetContainer()->AddMaterial<Engine::Graphics::PBRMaterial>("Orange", 9.0f, 6.0f, 0.0f, 1.0f);

        Engine::Scripts::RenderScript *renderScript = nullptr;
        Space::StarScript *starScript = nullptr;
        Space::CelestialBodyScript *celestialBodyScript = nullptr;
        auto sun = CreateGameObject("Sun_1");
        renderScript = sun->EmplaceScript<Engine::Scripts::RenderScript>(GetGraphics()->GetRenderManager());
        renderScript->EmplaceRenderUnit("MainShader", "Sphere", "Red_GLOW");
        starScript = sun->EmplaceScript<Space::StarScript>(space, GetGraphics());
        celestialBodyScript = sun->GetScript<Space::CelestialBodyScript>();
        celestialBodyScript->SetMass(1000000.0f);
        celestialBodyScript->SetRadius(30.0f);
        celestialBodyScript->SetVelocity(glm::vec3(0.0, 0.0f, 0.0f));

        auto greenPlanet = CreateGameObject("Planet_Green");
        renderScript = greenPlanet->EmplaceScript<Engine::Scripts::RenderScript>(GetGraphics()->GetRenderManager());
        renderScript->EmplaceRenderUnit("MainShader", "Sphere", "Green");
        celestialBodyScript = greenPlanet->EmplaceScript<Space::CelestialBodyScript>(space, GetGraphics());
        celestialBodyScript->SetMass(2000.0f);
        celestialBodyScript->SetRadius(4.0f);
        celestialBodyScript->SetVelocity(glm::vec3(0.0f, 0.0f, 1.1f));
        greenPlanet->GetTransform().SetPosition(70.6f, 0.0f, 6.9f);

        auto bluePlanet = CopyGameObject("Planet_Blue", *greenPlanet);
        renderScript = bluePlanet->GetScript<Engine::Scripts::RenderScript>();
        renderScript->Clear();
        renderScript->EmplaceRenderUnit("MainShader", "Sphere", "Blue");
        celestialBodyScript = bluePlanet->GetScript<Space::CelestialBodyScript>();
        celestialBodyScript->SetMass(2000.0f);
        celestialBodyScript->SetRadius(4.0f);
        celestialBodyScript->SetVelocity(glm::vec3(0.0f, 0.0f, 0.8f));
        bluePlanet->GetTransform().SetPosition(-189.f, 0.0f, 6.9f);

        auto redPlanet = CopyGameObject("Planet_Red", *greenPlanet);
        renderScript = redPlanet->GetScript<Engine::Scripts::RenderScript>();
        renderScript->Clear();
        renderScript->EmplaceRenderUnit("MainShader", "Sphere", "Red");
        celestialBodyScript = redPlanet->GetScript<Space::CelestialBodyScript>();
        celestialBodyScript->SetMass(4000.0f);
        celestialBodyScript->SetRadius(5.0f);
        celestialBodyScript->SetVelocity(glm::vec3(-1.0f, 0.0f, 0.0f));
        redPlanet->GetTransform().SetPosition(0.0f, 0.0f, -90.2f);

        auto purplePlanet = CopyGameObject("Planet_Purple", *greenPlanet);
        renderScript = purplePlanet->GetScript<Engine::Scripts::RenderScript>();
        renderScript->Clear();
        renderScript->EmplaceRenderUnit("MainShader", "Sphere", "Purple");
        celestialBodyScript = purplePlanet->GetScript<Space::CelestialBodyScript>();
        celestialBodyScript->SetMass(10000.0f);
        celestialBodyScript->SetRadius(7.0f);
        celestialBodyScript->SetVelocity(glm::vec3(0.0f, 0.0f, 0.6f));
        purplePlanet->GetTransform().SetPosition(212.0f, 0.0f, 5.6f);

        auto aquaPlanet = CopyGameObject("Planet_Aqua", *greenPlanet);
        renderScript = aquaPlanet->GetScript<Engine::Scripts::RenderScript>();
        renderScript->Clear();
        renderScript->EmplaceRenderUnit("MainShader", "Sphere", "Aqua");
        celestialBodyScript = aquaPlanet->GetScript<Space::CelestialBodyScript>();
        celestialBodyScript->SetMass(30000.0f);
        celestialBodyScript->SetRadius(10.0f);
        celestialBodyScript->SetVelocity(glm::vec3(0.0f, 0.0f, 0.45f));
        aquaPlanet->GetTransform().SetPosition(-486.0f, 0.0f, 0.0);

        auto pinkPlanet = CopyGameObject("Planet_Pink", *greenPlanet);
        renderScript = pinkPlanet->GetScript<Engine::Scripts::RenderScript>();
        renderScript->Clear();
        renderScript->EmplaceRenderUnit("MainShader", "Sphere", "Pink");
        celestialBodyScript = pinkPlanet->GetScript<Space::CelestialBodyScript>();
        celestialBodyScript->SetMass(40000.0f);
        celestialBodyScript->SetRadius(13.0f);
        celestialBodyScript->SetVelocity(glm::vec3(0.0f, 0.0f, 0.5f));
        pinkPlanet->GetTransform().SetPosition(500.0f, 0.0f, 0.0f);

        auto greenMoon = CopyGameObject("Moon_Green", *greenPlanet);
        renderScript = greenMoon->GetScript<Engine::Scripts::RenderScript>();
        celestialBodyScript = greenMoon->GetScript<Space::CelestialBodyScript>();
        celestialBodyScript->SetMass(100.0f);
        celestialBodyScript->SetRadius(2.0f);
        celestialBodyScript->SetVelocity(glm::vec3(0.1f, 0.0f, 0.2f));
        greenMoon->GetTransform().SetPosition(532.5f, 0.0f, -7.9f);

        auto blueMoon = CopyGameObject("Moon_Blue", *bluePlanet);
        renderScript = blueMoon->GetScript<Engine::Scripts::RenderScript>();
        celestialBodyScript = blueMoon->GetScript<Space::CelestialBodyScript>();
        celestialBodyScript->SetMass(100.0f);
        celestialBodyScript->SetRadius(2.0f);
        celestialBodyScript->SetVelocity(glm::vec3(0.0f, 0.0f, 0.7f));
        blueMoon->GetTransform().SetPosition(-511.8f, 0.0f, 12.0f);

        auto redMoon = CopyGameObject("Moon_Red", *redPlanet);
        renderScript = redMoon->GetScript<Engine::Scripts::RenderScript>();
        celestialBodyScript = redMoon->GetScript<Space::CelestialBodyScript>();
        celestialBodyScript->SetMass(100.0f);
        celestialBodyScript->SetRadius(2.0f);
        celestialBodyScript->SetVelocity(glm::vec3(0.0f, 0.0f, 0.2f));
        redMoon->GetTransform().SetPosition(464.5f, 0.0f, 2.9f);

        auto player = CreateGameObject("Player");
        Engine::Objects::SetPosition(player, 0.0f, 450.0f, 15.0f);
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
        ambient->GetLight().SetIntensity(0.04f);
        GetGraphics()->GetPostProcessing()->GetSettings().SetBloomThreshold(0.64f);
        GetGraphics()->GetPostProcessing()->GetSettings().SetExposure(0.5f);

        escape = GetInput()->GetScheme()->CreatePressableKey(GLFW_KEY_ESCAPE);
        escape->AddListenerOnPress(switchState);
        gameManager->AddListenerOnGameModeChanged(changeGameMode);
    }

    void MainScene::ChangeGameMode(EGameMode gameMode)
    {
        if (gameManager->GetGameModeType() == EGameMode::Space)
        {
            Resume();
        }
    }

    void MainScene::SwitchState()
    {
        if (gameManager->GetGameModeType() == EGameMode::Edit)
        {
            return;
        }

        if (!currentState)
        {
            Resume();
        }
        else
        {
            Pause();
        }
    }

    void MainScene::Pause()
    {
        GetGameObject("Player")->GetScript<Engine::Scripts::PlayerController>()->SetActive(false);
        GetInput()->GetScheme()->GetMouse()->EnableCursor(true);
        auto &menuContainer = GetUI()->GetMenuManager()->GetContainer();
        menuContainer.Get<Main::Space::SpaceTimeMenu>()->SetActive(true);
        menuContainer.Get<Main::Game::GameModeMenu>()->SetActive(true);
        currentState = false;
    }

    void MainScene::Resume()
    {
        GetGameObject("Player")->GetScript<Engine::Scripts::PlayerController>()->SetActive(true);
        GetInput()->GetScheme()->GetMouse()->EnableCursor(false);
        auto &menuContainer = GetUI()->GetMenuManager()->GetContainer();
        menuContainer.Get<Main::Space::SpaceTimeMenu>()->SetActive(false);
        menuContainer.Get<Main::Game::GameModeMenu>()->SetActive(false);
        currentState = true;
    }

    MainScene::~MainScene()
    {
        escape->RemoveListenerOnPress(switchState);
        gameManager->RemoveListenerOnGameModeChanged(changeGameMode);
    }

    void MainScene::Update()
    {

    }

    void MainScene::Render()
    {}
}