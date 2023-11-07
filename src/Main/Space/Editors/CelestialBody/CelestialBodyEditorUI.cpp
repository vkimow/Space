#include "Space/Editors/CelestialBody/CelestialBodyEditorUI.h"
#include "Space/Editors/CelestialBody/CelestialBodyEditor.h"
#include <imgui.h>
#include "Engine/Tools/Other/ImGui.h"

namespace Main::Space
{
    CelestialBodyEditorUI::CelestialBodyEditorUI(CelestialBodyEditor *const editor)
        : EditorUI(editor)
    {}

    void CelestialBodyEditorUI::UpdateInner()
    {
        auto editor = GetEditor<CelestialBodyEditor>();
        ImGui::DragVector3("Position", editor->position.GetBuffer());
        ImGui::DragFloat("Mass", editor->mass.GetBufferPtr(), 0.1f);
        ImGui::DragFloat("Radius", editor->radius.GetBufferPtr(), 0.1f);
        ImGui::DragVector3("Velocity", editor->velocity.GetBuffer());
    }
}