#include "Editor/EditorMode.h"

namespace Main::Editor
{
    EditorMode::EditorMode(Engine::UIModule *ui, Engine::Graphics::RenderManager *render)
        : scene(nullptr)
        , ui(ui)
        , objectsManager(ui->GetEditorManager(), render)
    {
        auto& menuContainer = ui->GetMenuManager()->GetContainer();
        menuContainer.Create<Main::Editor::GameObjectsMenu>(&objectsManager);
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

        ui->GetEditorManager()->SetActive(false);
    }

    void EditorMode::SetScene(Engine::Objects::Scene * value)
    {
        scene = value;
        objectsManager.SetScene(scene);
    }
}