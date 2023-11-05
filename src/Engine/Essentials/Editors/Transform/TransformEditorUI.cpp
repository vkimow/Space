#include "Engine/Essentials/Editors/Transform/TransformEditor.h"
#include "Engine/Essentials/Editors/Transform/TransformEditorUI.h"
#include "Engine/Tools/Other/ImGui.h"
#include <imgui.h>


namespace Engine::UI
{
    TransformEditorUI::TransformEditorUI(TransformEditor *const editor)
        : EditorUI(editor, false, true) 
    {}

    TransformEditorUI::~TransformEditorUI()
    {}

    void TransformEditorUI::UpdateInner()
    {
        TransformEditor *editor = GetEditor<TransformEditor>();
        ImGui::DragVector3(GetVariableName("Position").c_str(), editor->GetPosition().GetBuffer());
        ImGui::DragVector3(GetVariableName("Rotation").c_str(), editor->GetRotation().GetBuffer());
        ImGui::DragVector3(GetVariableName("Scale").c_str(), editor->GetScale().GetBuffer());
    }
}