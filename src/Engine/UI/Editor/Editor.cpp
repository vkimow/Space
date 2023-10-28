#include "Engine/UI/Editor/Editor.h"
#include "Engine/UI/Editor/EditorUI.h"
#include <imgui.h>

namespace Engine::UI
{
    Editor::Editor(const std::string &name, EditorUI *const ui)
        : name(name)
        , isActive(false)
        , target(nullptr)
        , ui(ui)
    {}

    Editor::~Editor()
    {
        delete ui;
    }

    void Editor::SetTarget(Objects::GameObject *const object)
    {
        target = object;
        UpdateFromTarget();
    }

    void Editor::SetActive(bool value)
    {
        isActive = value;
    }

    void Editor::Update()
    {
        ui->Update();
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

    Objects::GameObject *const Editor::GetTarget()
    {
        return target;
    }

    const Objects::GameObject *const Editor::GetTarget() const
    {
        return target;
    }
}