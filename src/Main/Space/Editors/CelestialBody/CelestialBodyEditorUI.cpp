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
        ImGui::InputFloat("Mass", editor->mass.GetBufferPtr());
        ImGui::InputVector3("Velocity", editor->velocity.GetBuffer());
    }
}