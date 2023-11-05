#pragma once

#include "Engine/UI/Editor/EditorUI.h"

namespace Engine::UI
{
    class TransformEditor;
    class TransformEditorUI final: public EditorUI
    {
        friend class TransformEditor;

    private:
        TransformEditorUI(TransformEditor *const editor);
        TransformEditorUI(const TransformEditorUI &rhs) = delete;
        TransformEditorUI(TransformEditorUI &&rhs) noexcept = delete;
        TransformEditorUI &operator=(const TransformEditorUI &rhs) = delete;
        TransformEditorUI &operator=(TransformEditorUI &&rhs) noexcept = delete;
        ~TransformEditorUI();

    protected:
        void UpdateInner() override final;
    };
}