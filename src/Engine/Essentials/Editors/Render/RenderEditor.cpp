#include "Engine/Essentials/Editors/Render/RenderEditor.h"
#include "Engine/Essentials/Editors/Render/RenderEditorUI.h"
#include "Engine/Essentials/Scripts/Visuals/RenderScript.h"

namespace Engine::UI
{
    RenderEditor::RenderEditor()
        : Editor("Render", new RenderEditorUI(this))
    {}

    RenderEditor::~RenderEditor()
    {}

    size_t RenderEditor::GetDefaultPriority() const
    {
        return priority;
    }

    std::type_index RenderEditor::GetScriptType() const
    {
        return std::type_index(typeid(Scripts::RenderScript));
    }

    void RenderEditor::UpdateFromTarget()
    {
    }

    void RenderEditor::UpdateFromUI()
    {
    }
}