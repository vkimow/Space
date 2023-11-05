#include "Engine/UI/Editor/Editor.h"
#include "Engine/UI/Editor/EditorUI.h"
#include <imgui.h>

namespace Engine::UI
{
    Editor::Editor(const std::string &name, EditorUI *const ui, bool scriptCanBeDisactivated)
        : name(name)
        , isActive(true)
        , target(nullptr)
        , targetScript(nullptr)
        , ui(ui)
        , isScriptActive(true)
        , scriptCanBeDisactivated(scriptCanBeDisactivated)
    {}

    Editor::~Editor()
    {
        delete ui;
    }

    void Editor::SetTarget(Objects::GameObject *const object)
    {
        target = object;
        if (scriptCanBeDisactivated)
        {
            isScriptActive = object->GetScript(GetScriptType())->isActive;
        }
        UpdateFromTarget();
    }

    void Editor::SetActive(bool value)
    {
        isActive = value;
    }

    void Editor::Update()
    {
        ui->Update();
        if (scriptCanBeDisactivated && isScriptActive.IsValueDiffersFromBuffer())
        {
            isScriptActive.SetValueToBuffer();
            GetTarget()->GetScript(GetScriptType())->SetActive(isScriptActive);
        }
        UpdateFromUI();
    }

    bool Editor::IsActive() const
    {
        return isActive && target;
    }

    const std::string& Editor::GetName() const
    {
        return name;
    }

    Objects::GameObject *const Editor::GetTarget() const
    {
        return target;
    }
}