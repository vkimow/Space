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
        container.Create<TransformEditor>();
        container.Create<LightSourceEditor>();
    }

    EditorManager::~EditorManager()
    {}

    void EditorManager::SetTarget(Objects::GameObject *const object)
    {
        if (target)
        {
            UnsetTarget();
        }

        Editor *editor = nullptr;
        std::unordered_set<std::type_index> scriptsOfUnwantedEditors;
        std::vector<Editor *> editorsToEnable;
        for (auto it = object->GetScripts().begin(); it != object->GetScripts().end(); ++it)
        {
            if (container.ContainsByScript(it->type))
            {
                editor = container.GetByScript(it->type);
                editorsToEnable.push_back(editor);
                auto itEditorsToDisable = editor->EditorsToDisable();
                if (itEditorsToDisable)
                {
                    scriptsOfUnwantedEditors.insert(editor->EditorsToDisable()->begin(), editor->EditorsToDisable()->end());
                }
            }
        }

        editor = container.Get<GameObjectEditor>();
        editor->SetTarget(object);
        editor->SetActive(!scriptsOfUnwantedEditors.contains(editor->GetScriptType()));

        editor = container.Get<TransformEditor>();
        editor->SetTarget(object);
        editor->SetActive(!scriptsOfUnwantedEditors.contains(editor->GetScriptType()));

        for (auto it = editorsToEnable.begin(); it != editorsToEnable.end(); ++it)
        {
            editor = *it;
            editor->SetTarget(object);
            bool isActive = !scriptsOfUnwantedEditors.contains(editor->GetScriptType());
            editor->SetActive(isActive);
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

