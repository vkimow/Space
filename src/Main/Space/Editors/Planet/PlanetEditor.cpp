#include "Space/Editors/Planet/PlanetEditor.h"
#include "Space/Editors/Planet/PlanetEditorUI.h"
#include "Space/Scripts/PlanetScript.h"

namespace Main::Space
{
    PlanetEditor::PlanetEditor()
        :Editor("Planet", new PlanetEditorUI(this))
    {}

    PlanetEditor::~PlanetEditor()
    {}

    size_t PlanetEditor::GetDefaultPriority() const
    {
        return priority;
    }

    std::type_index PlanetEditor::GetScriptType() const
    {
        return std::type_index(typeid(PlanetScript));
    }

    void PlanetEditor::UpdateFromTarget()
    {}

    void PlanetEditor::UpdateFromUI()
    {}
}