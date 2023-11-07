#include "Editor/EditorMode.h"

namespace Main::Editor
{
    EditorMode::EditorMode(Engine::UIModule *ui, Engine::GraphicsModule *graphics)
        : scene(nullptr)
        , ui(ui)
        , objectsManager(ui->GetEditorManager(), graphics->GetRenderManager())
    {
        auto& menuContainer = ui->GetMenuManager()->GetContainer();
        menuContainer.Create<Main::Editor::GameObjectsMenu>(&objectsManager);
        menuContainer.Create<Engine::UI::GlobalLightingMenu>(graphics->GetLightManager());
        menuContainer.Create<Engine::UI::PostProcessingMenu>(graphics->GetPostProcessing());
    }

    EditorMode::~EditorMode()
    {
        auto &menuContainer = ui->GetMenuManager()->GetContainer();
        menuContainer.Remove<Main::Editor::GameObjectsMenu>();
    }

    void EditorMode::Start()
    {
        auto &menuContainer = ui->GetMenuManager()->GetContainer();
        menuContainer.Get<Main::Editor::GameObjectsMenu>()->SetActive(true);
        menuContainer.Get<Engine::UI::GlobalLightingMenu>()->SetActive(true);
        menuContainer.Get<Engine::UI::PostProcessingMenu>()->SetActive(true);
        ui->GetEditorManager()->SetActive(true);
    }

    void EditorMode::Update()
    {
        objectsManager.UpdateAll();
    }

    void EditorMode::End()
    {
        objectsManager.Deselect();

        auto &menuContainer = ui->GetMenuManager()->GetContainer();
        menuContainer.Get<Main::Editor::GameObjectsMenu>()->SetActive(false);
        menuContainer.Get<Engine::UI::GlobalLightingMenu>()->SetActive(false);
        menuContainer.Get<Engine::UI::PostProcessingMenu>()->SetActive(false);

        ui->GetEditorManager()->SetActive(false);
    }

    void EditorMode::SetScene(Engine::Objects::Scene * value)
    {
        scene = value;
        objectsManager.SetScene(scene);
    }
}