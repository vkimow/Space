#include "Engine/Essentials/Editors/GameObject/GameObjectEditor.h"
#include "Engine/Essentials/Editors/GameObject/GameObjectEditorUI.h"
#include "Engine/Tools/Other/ImGui.h"
#include <imgui.h>


namespace Engine::UI
{
    GameObjectEditorUI::GameObjectEditorUI(GameObjectEditor *const editor)
        : EditorUI(editor, true, true)
    {}

    GameObjectEditorUI::~GameObjectEditorUI()
    {}

    void GameObjectEditorUI::UpdateInner()
    {
        GameObjectEditor *editor = GetEditor<GameObjectEditor>();
        std::string targetName = GetVariableName(editor->GetTargetName());
        ImGui::Checkbox(targetName.c_str(), editor->GetIsActive().GetBufferPtr());
    }
}