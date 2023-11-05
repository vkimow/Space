#include "Engine/Essentials/Editors/Render/RenderEditor.h"
#include "Engine/Essentials/Editors/Render/RenderEditorUI.h"
#include "Engine/Tools/Other/ImGui.h"
#include <imgui.h>


namespace Engine::UI
{
    RenderEditorUI::RenderEditorUI(RenderEditor *const editor)
        : EditorUI(editor, true)
    {}

    RenderEditorUI::~RenderEditorUI()
    {}

    void RenderEditorUI::UpdateInner()
    {
        RenderEditor *editor = GetEditor<RenderEditor>();
    }
}