#include "Engine/UI/Editor/EditorManager.h"
#include "Engine/Essentials/Editors/EditorsHeader.h"
#include <imgui.h>

namespace Engine::UI
{
    EditorManager::EditorManager()
        : container()
        , target(nullptr)
        , isActive(false)
    {
        container.Create<GameObjectEditor>();
    }

    EditorManager::~EditorManager()
    {}

    void EditorManager::SetTarget(Objects::GameObject *const object)
    {
        if (target)
        {
            UnsetTarget();
        }

        Editor *editor = container.Get<GameObjectEditor>();
        editor->SetTarget(object);
        editor->SetActive(true);

        for (auto it = object->GetScripts().begin(); it != object->GetScripts().end(); ++it)
        {
            if (container.ContainsByScript(it->type))
            {
                editor = container.GetByScript(it->type);
                editor->SetTarget(object);
                editor->SetActive(true);
            }
        }

        target = object;
    }

    void EditorManager::UnsetTarget()
    {
        for (auto it = container.begin(); it != container.end(); ++it)
        {
            it->element->SetActive(false);
        }
        target = nullptr;
    }

    void EditorManager::SetActive(bool value)
    {
        isActive = value;
    }

    bool EditorManager::IsActive() const
    {
        return isActive && target;
    }

    EditorContainer &EditorManager::GetContainer()
    {
        return container;
    }

    void EditorManager::Update()
    {
        if (!IsActive())
        {
            return;
        }

        ImGui::Begin("Editor", &isActive);
        for (auto it = container.begin(); it != container.end(); ++it)
        {
            if (it->element->IsActive())
            {
                it->element->Update();
            }
        }
        ImGui::End();
    }
}

