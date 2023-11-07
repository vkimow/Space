#include "Editor/GameObjectManager.h"

namespace Main::Editor
{
    GameObjectManager::GameObjectManager(Engine::UI::EditorManager *uiEditor, Engine::Graphics::RenderManager *render)
        : scene(nullptr)
        , uiEditor(uiEditor)
        , render(render)
        , selectedObject(nullptr)
    {}

    GameObjectManager::~GameObjectManager()
    {
        Deselect();
    }

    void GameObjectManager::SetScene(Engine::Objects::Scene *value)
    {
        Deselect();
        scene = value;
    }

    void GameObjectManager::UpdateAll()
    {
        Engine::Objects::GameObject *gameObject;
        for (auto it = scene->GetGameObjects().begin(); it != scene->GetGameObjects().end(); ++it)
        {
            gameObject = it->element;
            if (!gameObject->IsActive())
            {
                continue;
            }

            gameObject->UpdateEditor();
        }

        if (selectedObject)
        {
            auto forward = render->GetUnitBuilder().Create("MainShader", "Forward", "Blue", nullptr, selectedObject->GetTransformPtr());
            auto right = render->GetUnitBuilder().Create("MainShader", "Right", "Red", nullptr, selectedObject->GetTransformPtr());
            auto Up = render->GetUnitBuilder().Create("MainShader", "Up", "Green", nullptr, selectedObject->GetTransformPtr());

            render->GetPool().AddRenderUnit(forward);
            render->GetPool().AddRenderUnit(right);
            render->GetPool().AddRenderUnit(Up);
        }
    }

    void GameObjectManager::Select(const std::string &name)
    {
        Select(scene->GetGameObject(name));
    }

    void GameObjectManager::Select(Engine::Objects::GameObject * object)
    {
        Deselect();
        uiEditor->SetActive(true);
        uiEditor->SetTarget(object);
        selectedObject = object;
        selectedObject->SelectEditor();
    }

    void GameObjectManager::Deselect()
    {
        if (selectedObject)
        {
            uiEditor->UnsetTarget();
            selectedObject->DeselectEditor();
            selectedObject = nullptr;
        }
    }

    Engine::Objects::GameObject *const GameObjectManager::GetGameObject(const std::string &name)
    {
        return scene->GetGameObject(name);
    }

    const Engine::Objects::GameObject *const GameObjectManager::GetGameObject(const std::string &name) const
    {
        return scene->GetGameObject(name);
    }

    GameObjectManager::GameObjectsContainer &GameObjectManager::GetGameObjects()
    {
        return scene->GetGameObjects();
    }

    const GameObjectManager::GameObjectsContainer &GameObjectManager::GetGameObjects() const
    {
        return scene->GetGameObjects();
    }
}

