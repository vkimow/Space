#pragma once

#include "Engine/UI/Editor/EditorUI.h"

namespace Main::Space
{
    class StarEditor;
    class StarEditorUI final: public Engine::UI::EditorUI
    {
        friend class StarEditor;

    private:
        StarEditorUI(StarEditor *const editor);
        StarEditorUI(const StarEditorUI &rhs) = delete;
        StarEditorUI(StarEditorUI &&rhs) noexcept = delete;
        StarEditorUI &operator=(const StarEditorUI &rhs) = delete;
        StarEditorUI &operator=(StarEditorUI &&rhs) noexcept = delete;
        ~StarEditorUI() = default;

    protected:
        void UpdateInner() override final;
    };
}