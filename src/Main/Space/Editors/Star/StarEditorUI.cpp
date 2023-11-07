#include "Space/Editors/Star/StarEditorUI.h"
#include "Space/Editors/Star/StarEditor.h"
#include <imgui.h>
#include "Engine/Tools/Other/ImGui.h"

namespace Main::Space
{
    StarEditorUI::StarEditorUI(StarEditor *const editor)
        : EditorUI(editor)
    {}

    void StarEditorUI::UpdateInner()
    {
        auto editor = GetEditor<StarEditor>();  
        ImGui::LightValue("Diffuse", editor->diffuse.GetBuffer());
        ImGui::LightValue("Specular", editor->specular.GetBuffer());
    }
}