#include "Engine/Essentials/Editors/GameObject/GameObjectEditor.h"
#include "Engine/Essentials/Editors/GameObject/GameObjectEditorUI.h"


namespace Engine::UI
{
    GameObjectEditor::GameObjectEditor()
        : Editor("GameObject", new GameObjectEditorUI(this), false)
        , isActive(false)
    {}

    GameObjectEditor::~GameObjectEditor()
    {}

    size_t GameObjectEditor::GetDefaultPriority() const
    {
        return priority;
    }

    std::type_index GameObjectEditor::GetScriptType() const
    {
        return std::type_index(typeid(Objects::GameObject));
    }

    void GameObjectEditor::UpdateFromTarget()
    {
        isActive = GetTarget()->IsActive();
    }

    void GameObjectEditor::UpdateFromUI()
    {
        if (isActive.IsValueDiffersFromBuffer())
        {
            isActive.SetValueToBuffer();
            GetTarget()->SetActive(isActive);
        }
    }

    const std::string &GameObjectEditor::GetTargetName() const
    {
        return GetTarget()->GetName();
    }

    Buffer<bool> &GameObjectEditor::GetIsActive()
    {
        return isActive;
    }
}