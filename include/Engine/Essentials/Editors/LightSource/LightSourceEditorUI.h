#pragma once

#include "Engine/UI/Editor/EditorUI.h"

namespace Engine::UI
{
    class LightSourceEditor;
    class LightSourceEditorUI final: public EditorUI
    {
        friend class LightSourceEditor;

    private:
        LightSourceEditorUI(LightSourceEditor *const editor);
        LightSourceEditorUI(const LightSourceEditorUI &rhs) = delete;
        LightSourceEditorUI(LightSourceEditorUI &&rhs) noexcept = delete;
        LightSourceEditorUI &operator=(const LightSourceEditorUI &rhs) = delete;
        LightSourceEditorUI &operator=(LightSourceEditorUI &&rhs) noexcept = delete;
        ~LightSourceEditorUI();

    protected:
        void UpdateInner() override final;
    };
}