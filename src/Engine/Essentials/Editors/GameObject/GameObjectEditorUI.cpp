#include "Engine/Essentials/Editors/GameObject/GameObjectEditor.h"
#include "Engine/Essentials/Editors/GameObject/GameObjectEditorUI.h"
#include <imgui.h>


namespace Engine::UI
{
    GameObjectEditorUI::GameObjectEditorUI(GameObjectEditor *const editor)
        : EditorUI(editor)
    {}

    GameObjectEditorUI::~GameObjectEditorUI()
    {}

    void GameObjectEditorUI::UpdateInner()
    {
        GameObjectEditor *editor = GetEditor<GameObjectEditor>();
        ImGui::Text("Name: '%s'", editor->GetTargetName().c_str());
        ImGui::Checkbox("Is Active", editor->GetIsActive());
        ImGui::InputFloat3("Position", editor->GetPosition());
        ImGui::InputFloat3("Rotation", editor->GetRotation());
        ImGui::InputFloat3("Scale", editor->GetScale());
    }
}