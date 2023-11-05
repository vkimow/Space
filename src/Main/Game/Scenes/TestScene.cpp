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

        GetGraphics()->GetContainer()->AddMesh("Cube", Engine::Graphics::Cube());
        GetGraphics()->GetContainer()->AddMesh("Plane", Engine::Graphics::Plane());
        GetGraphics()->GetContainer()->AddMesh("Sphere", Engine::Graphics::Sphere());
        GetGraphics()->GetContainer()->AddLine("Forward", glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, -15.0f));
        GetGraphics()->GetContainer()->AddLine("Up", glm::vec3(0.0f), glm::vec3(0.0f, 15.0f, 0.0f));
        GetGraphics()->GetContainer()->AddLine("Right", glm::vec3(0.0f), glm::vec3(15.0f, 0.0f, 0.0f));

        auto cube = CreateGameObject("Cube_1");
        Engine::Scripts::RenderScript *renderScript = cube->EmplaceScript<Engine::Scripts::RenderScript>(GetGraphics()->GetRenderManager());
        renderScript->EmplaceRenderUnit("MainShader", "Cube");
        CopyGameObject("Cube_Forward", *cube);
        CopyGameObject("Cube_Up", *cube);
        CopyGameObject("Cube_Right", *cube); 

        Engine::Objects::SetPosition(GetGameObject("Cube_Forward"), 0.0f, 0.0f, -3.0f);
        Engine::Objects::SetPosition(GetGameObject("Cube_Up"), 0.0f, 3.0f, 0.0f);
        Engine::Objects::SetPosition(GetGameObject("Cube_Right"), 3.0f, 0.0f, 0.0f);

        Engine::Objects::SetScale(GetGameObject("Cube_Forward"), 0.5f, 0.5f, 0.5f);
        Engine::Objects::SetScale(GetGameObject("Cube_Up"), 0.5f, 0.5f, 0.5f);
        Engine::Objects::SetScale(GetGameObject("Cube_Right"), 0.5f, 0.5f, 0.5f);
        GetGameObject("Cube_1")->SetActive(false);

        auto plane = CreateGameObject("Plane_1");
        renderScript = plane->EmplaceScript<Engine::Scripts::RenderScript>(GetGraphics()->GetRenderManager());
        renderScript->EmplaceRenderUnit("MainShader", "Plane");
        Engine::Objects::SetPosition(plane, 0.0f, -2.0f, 0.0f);
        Engine::Objects::SetScale(plane, 10.0f, 10.0f, 10.0f);

        auto sphere = CreateGameObject("Sphere_1");
        renderScript = sphere->EmplaceScript<Engine::Scripts::RenderScript>(GetGraphics()->GetRenderManager());
        renderScript->EmplaceRenderUnit("MainShader", "Sphere");

        auto player = CreateGameObject("Player");
        Engine::Objects::SetPosition(player, 0.0f, 0.0f, 10.0f);
        Engine::Objects::SetRotationInDegrees(player, 0.0f, 0.0f, 0.0f);

        auto scheme = GetInput()->GetScheme();
        auto movementInput = scheme->CreateVectorPressable(GLFW_KEY_D, GLFW_KEY_A, GLFW_KEY_W, GLFW_KEY_S);
        auto verticalInput = scheme->CreateDeltaPressable(GLFW_KEY_SPACE, GLFW_KEY_LEFT_CONTROL);
        auto mouseInput = scheme->GetMouse()->GetDeltaPositionInput();
        auto rollInput = scheme->CreateDeltaPressable(GLFW_KEY_Q, GLFW_KEY_E);
        key = scheme->CreatePressableKey(GLFW_KEY_C);
        player->EmplaceScript<Engine::Scripts::PlayerController>(movementInput->GetDeltaX(), verticalInput, movementInput->GetDeltaY(), mouseInput->GetDeltaY(), mouseInput->GetDeltaX(), rollInput, 10.0f, 100.0f);

        auto projection = Engine::Graphics::Projection(90, window->GetResolution(), 0.01f, 100000.0f);
        auto vCamera = GetGraphics()->GetCameraManager()->AddVirtualCamera<Engine::Graphics::VirtualCamera>("Player Camera", projection);
        player->EmplaceScript<Engine::Scripts::CameraScript>(vCamera);

        auto ambient = GetGraphics()->GetLightManager()->GetContainer().InitializeAmbientLight();
        ambient->GetLight().SetIntensity(0.2f);

        auto directional = GetGraphics()->GetLightManager()->GetContainer().InitializeDirectionalLight();
        directional->GetDiffuse().SetColor(0.5, 1.0f, 0.5f);
        directional->GetDiffuse().SetIntensity(1.0f);
        directional->GetSpecular().SetColor(0.0f, 0.0f, 1.0f);
        directional->GetSpecular().SetIntensity(1.0f);
        directional->SetDirection(1, -1, -1);

        auto pointLight = CreateGameObject("PointLight");
        auto pointLightScript = pointLight->EmplaceScript<Engine::Scripts::LightSourceScript>(GetGraphics()->GetLightManager(), Engine::Graphics::LightSourceType::PointLight);

        auto spotLight = CreateGameObject("SpotLight");
        auto spotLightScript = spotLight->EmplaceScript<Engine::Scripts::LightSourceScript>(GetGraphics()->GetLightManager(), Engine::Graphics::LightSourceType::SpotLight);
    }

    TestScene::~TestScene()
    {}

    void TestScene::Update()
    {
    }

    void TestScene::Render()
    {}
}