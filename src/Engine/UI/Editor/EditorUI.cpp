#include "Engine/UI/Editor/EditorUI.h"

#include <imgui.h>
#include "Engine/UI/Editor/Editor.h"

namespace Engine::UI
{
    EditorUI::EditorUI(Editor *const editor)
        : editor(editor)
    {}

    EditorUI::~EditorUI()
    {}

    void EditorUI::Update()
    {
        if (ImGui::CollapsingHeader(editor->GetName().c_str(), ImGuiTreeNodeFlags_DefaultOpen))
        {
            UpdateInner();
        }
    }
}

