#include "Space/Editors/Planet/PlanetEditorUI.h"
#include "Space/Editors/Planet/PlanetEditor.h"
#include <imgui.h>

namespace Main::Space
{
    PlanetEditorUI::PlanetEditorUI(PlanetEditor *const editor)
        : EditorUI(editor)
    {}

    void PlanetEditorUI::UpdateInner()
    {}
}