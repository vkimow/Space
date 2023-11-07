#include "Space/Editors/Star/StarEditor.h"
#include "Space/Editors/Star/StarEditorUI.h"
#include "Space/Scripts/StarScript.h"
#include "Engine/Graphics/Light/LightSource.h"

namespace Main::Space
{
    const std::unordered_set<std::type_index> StarEditor::editorsToDisable = {
        std::type_index(typeid(Engine::Scripts::LightSourceScript))
    };

    StarEditor::StarEditor()
        : Editor("Star", new StarEditorUI(this))
        , diffuse()
        , specular()
    {}

    StarEditor::~StarEditor()
    {}

    size_t StarEditor::GetDefaultPriority() const
    {
        return priority;
    }

    std::type_index StarEditor::GetScriptType() const
    {
        return std::type_index(typeid(StarScript));
    }

    const std::unordered_set<std::type_index> *const StarEditor::EditorsToDisable() const
    {
        return &editorsToDisable;
    }

    void StarEditor::UpdateFromTarget()
    {
        auto lightScript = GetScriptFromTarget<Engine::Scripts::LightSourceScript>();
        diffuse = lightScript->GetLightSource()->GetDiffuse();
        specular = lightScript->GetLightSource()->GetSpecular();
    }

    void StarEditor::UpdateFromUI()
    {
        auto lightScript = GetScriptFromTarget<Engine::Scripts::LightSourceScript>();
        if (diffuse.IsValueDiffersFromBuffer())
        {
            diffuse.SetValueToBuffer();
            lightScript->GetLightSource()->GetDiffuse() = diffuse;
        }
        if (specular.IsValueDiffersFromBuffer())
        {
            specular.SetValueToBuffer();
            lightScript->GetLightSource()->GetSpecular() = specular;
        }
    }
}