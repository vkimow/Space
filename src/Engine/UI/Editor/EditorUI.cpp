#include "Engine/UI/Editor/EditorUI.h"
#include "Engine/Tools/Other/ImGui.h"

#include <imgui.h>
#include "Engine/UI/Editor/Editor.h"

namespace Engine::UI
{
    EditorUI::EditorUI(Editor *const editor, bool shouldNotUseCollapsingHeader, bool shouldNotBeDisabled)
        : editor(editor)
        , shouldNotUseCollapsingHeader(shouldNotUseCollapsingHeader)
        , shouldNotBeDisabled(shouldNotBeDisabled)
    {}

    EditorUI::~EditorUI()
    {}

    void EditorUI::Update()
    {
        if (shouldNotUseCollapsingHeader)
        {
            UpdateInner();
            return;
        }

        if (!shouldNotBeDisabled)
        {
            std::string activeLabel = ImGui::GetInvisibleLabel("Active", editor->GetName().c_str());
            ImGui::Checkbox(activeLabel.c_str(), GetEditor()->isScriptActive.GetBufferPtr());
            ImGui::SameLine();
        }

        if (ImGui::CollapsingHeader(editor->GetName().c_str(), ImGuiTreeNodeFlags_DefaultOpen))
        {
            UpdateInner();
        }
    }

    std::string EditorUI::GetVariableName(const std::string &name) const
    {
        return ImGui::GetLabel(name, GetEditor()->GetName());
    }

    const std::string &EditorUI::GetEditorName() const
    {
        return GetEditor()->GetName();
    }

}

