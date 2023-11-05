#pragma once

#include "Engine/UI/Editor/EditorUI.h"

namespace Engine::UI
{
    class RenderEditor;
    class RenderEditorUI final: public EditorUI
    {
        friend class RenderEditor;

    private:
        RenderEditorUI(RenderEditor *const editor);
        RenderEditorUI(const RenderEditorUI &rhs) = delete;
        RenderEditorUI(RenderEditorUI &&rhs) noexcept = delete;
        RenderEditorUI &operator=(const RenderEditorUI &rhs) = delete;
        RenderEditorUI &operator=(RenderEditorUI &&rhs) noexcept = delete;
        ~RenderEditorUI();

    protected:
        void UpdateInner() override final;
    };
}