#include "Game/Scenes/TestScene.h"

#include <numbers>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include "Game/Menus/MenusHeader.h"
#include "Shaders/ShaderCreator.h"


namespace Main::Game
{
    TestScene::TestScene(const std::string &name, Engine::Window *const window, Engine::Engine *const engine, Space::SpaceManager *const space)
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
        GetGraphics()->GetContainer()->AddMaterial<Engine::Graphics::PBRMaterial>("Blue_GLOW", 30.0f, 40.0f, 100.0f, 1.0f);
        GetGraphics()->GetContainer()->AddMaterial<Engine::Graphics::PBRMaterial>("Red", 1.0f, 0.0f, 0.0f, 1.0f);
        GetGraphics()->GetContainer()->AddMaterial<Engine::Graphics::PBRMaterial>("Green", 0.0f, 1.0f, 0.0f, 1.0f);
        GetGraphics()->GetContainer()->AddMaterial<Engine::Graphics::PBRMaterial>("Blue", 0.0f, 0.0f, 1.0f, 1.0f);
        GetGraphics()->GetContainer()->AddMaterial<Engine::Graphics::PBRMaterial>("Orange", 3.0f, 2.00f, 0.0f, 1.0f);
        GetGraphics()->GetContainer()->AddMaterial<Engine::Graphics::PBRMaterial>("White", 1.0f, 1.0f, 1.0f, 1.0f);

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

        auto greenPlanet = CreateGameObject("Planet_Green");
        renderScript = greenPlanet->EmplaceScript<Engine::Scripts::RenderScript>(GetGraphics()->GetRenderManager());
        renderScript->EmplaceRenderUnit("MainShader", "Sphere", "Green");
        celestialBodyScript = greenPlanet->EmplaceScript<Space::CelestialBodyScript>(space, GetGraphics());
        celestialBodyScript->SetMass(1000000.0f);
        celestialBodyScript->SetVelocity(glm::vec3(0.0, 0.0f, 0.0f));
        celestialBodyScript->SetRadius(1.0f);

        auto bluePlanet = CopyGameObject("Planet_Blue", *greenPlanet);
        renderScript = bluePlanet->GetScript<Engine::Scripts::RenderScript>();
        renderScript->Clear();
        renderScript->EmplaceRenderUnit("MainShader", "Sphere", "Blue");
        celestialBodyScript = bluePlanet->GetScript<Space::CelestialBodyScript>();
        celestialBodyScript->SetRadius(0.3f);

        auto redPlanet = CopyGameObject("Planet_Red", *greenPlanet);
        renderScript = redPlanet->GetScript<Engine::Scripts::RenderScript>();
        renderScript->Clear();
        renderScript->EmplaceRenderUnit("MainShader", "Sphere", "Red");
        celestialBodyScript = redPlanet->GetScript<Space::CelestialBodyScript>();
        celestialBodyScript->SetRadius(0.2f);

        //auto plane = CreateGameObject("Plane_1");
        //renderScript = plane->EmplaceScript<Engine::Scripts::RenderScript>(GetGraphics()->GetRenderManager());
        //renderScript->EmplaceRenderUnit("MainShader", "Plane", "White");
        //Engine::Objects::SetPosition(plane, 0.0f, -5.0f, 0.0f);
        //Engine::Objects::SetScale(plane, 100.0f, 100.0f, 100.0f);

        auto player = CreateGameObject("Player");
        Engine::Objects::SetPosition(player, -0.297f, -0.885f, 2.913f);
        Engine::Objects::SetRotationInDegrees(player, 27.106f, -29.583f, -70.867f);

        //auto scheme = GetInput()->GetScheme();
        //auto movementInput = scheme->CreateVectorPressable(GLFW_KEY_D, GLFW_KEY_A, GLFW_KEY_W, GLFW_KEY_S);
        //auto verticalInput = scheme->CreateDeltaPressable(GLFW_KEY_SPACE, GLFW_KEY_LEFT_CONTROL);
        //auto mouseInput = scheme->GetMouse()->GetDeltaPositionInput();
        //auto rollInput = scheme->CreateDeltaPressable(GLFW_KEY_Q, GLFW_KEY_E);
        //player->EmplaceScript<Engine::Scripts::PlayerController>(movementInput->GetDeltaX(), verticalInput, movementInput->GetDeltaY(), mouseInput->GetDeltaY(), mouseInput->GetDeltaX(), rollInput, 10.0f, 100.0f);

        auto projection = Engine::Graphics::Projection(window, 120, 0.01f, 100000.0f);
        auto vCamera = GetGraphics()->GetCameraManager()->AddVirtualCamera<Engine::Graphics::VirtualCamera>("Player Camera", projection);
        player->EmplaceScript<Engine::Scripts::CameraScript>(vCamera);

        auto ambient = GetGraphics()->GetLightManager()->GetContainer().InitializeAmbientLight();
        ambient->GetLight().SetIntensity(0.04f);

        GetGraphics()->GetPostProcessing()->GetSettings().SetBloomThreshold(0.5f);
        GetGraphics()->GetPostProcessing()->GetSettings().SetExposure(0.25f);
    }

    TestScene::~TestScene()
    {}

    void TestScene::Update()
    {
        float radiusSun = 200.f;
        float radiusMoon1 = 2.f;
        float radiusMoon2 = 3.f;

        float time = GetTime()->GetGlobalTime() * 1.f;
        float xSun = cosf(time) * radiusSun;
        float ySun = sinf(time) * radiusSun;
        float xMoon = cosf(time * 3) * radiusMoon1;
        float yMoon = sinf(time * 3) * radiusMoon1;
        float xMoon2 = cosf(time * 5) * radiusMoon2;
        float yMoon2 = sinf(time * 5) * radiusMoon2;

        Engine::Objects::SetPosition(GetGameObject("Sun_1"), 0.0f, ySun, xSun);
        Engine::Objects::SetPosition(GetGameObject("Planet_Blue"), xMoon, 0.0f, yMoon);

        glm::vec3 moonPositon = GetGameObject("Planet_Blue")->GetTransform().GetPosition();
        Engine::Objects::SetPosition(GetGameObject("Planet_Red"), 0.0f, yMoon2, xMoon2);

    }

    void TestScene::Render()
    {}
}