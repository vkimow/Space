#include "Space/SpaceMode.h"
#include "Space/Menus/MenusHeader.h"

namespace Main::Space
{
    SpaceMode::SpaceMode(Engine::UIModule *ui)
        : scene(nullptr)
        , ui(ui)
        , objectsManager()
        , spaceManager(&objectsManager)
    {
        auto &menuContainer = ui->GetMenuManager()->GetContainer();
        menuContainer.Create<SpaceTimeMenu>(spaceManager.GetTime());
    }

    SpaceMode::~SpaceMode()
    {}

    void SpaceMode::Start()
    {
        auto &menuContainer = ui->GetMenuManager()->GetContainer();
        menuContainer.Get<SpaceTimeMenu>()->SetActive(true);
    }

    void SpaceMode::Update()
    {
        objectsManager.UpdateAll();
        spaceManager.Update();
    }

    void SpaceMode::End()
    {
        auto &menuContainer = ui->GetMenuManager()->GetContainer();
        menuContainer.Get<SpaceTimeMenu>()->SetActive(false);
    }

    void SpaceMode::SetScene(Engine::Objects::Scene *value)
    {
        scene = value;
        objectsManager.SetScene(scene);
    }
}