#include "Space/SpaceMode.h"
#include "Space/Menus/MenusHeader.h"
#include "Space/Editors/EditorsHeader.h"
#include <Game/Menus/GameMode/GameModeMenu.h>

namespace Main::Space
{
    SpaceMode::SpaceMode(Engine::UIModule *ui, Engine::GraphicsModule *graphics, Engine::InputModule *input)
        : scene(nullptr)
        , ui(ui)
        , input(input)
        , objectsManager()
        , spaceManager(graphics->GetContainer())
    {
        auto &menuContainer = ui->GetMenuManager()->GetContainer();
        menuContainer.Create<SpaceTimeMenu>(&(spaceManager.GetTime()));

        auto &editorContainer = ui->GetEditorManager()->GetContainer();
        editorContainer.Create<CelestialBodyEditor>();
        editorContainer.Create<StarEditor>();
    }

    SpaceMode::~SpaceMode()
    {}

    void SpaceMode::Start()
    {}

    void SpaceMode::Update()
    {
        spaceManager.Update();
        objectsManager.UpdateAll();
    }

    void SpaceMode::End()
    {}

    void SpaceMode::SetScene(Engine::Objects::Scene *value)
    {
        scene = value;
        objectsManager.SetScene(scene);
    }

    SpaceManager &SpaceMode::GetSpaceManager()
    {
        return spaceManager;
    }

    const SpaceManager &SpaceMode::GetSpaceManager() const
    {
        return spaceManager;
    }
}