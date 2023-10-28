#pragma once

#include "Engine/UI/Editor/EditorUI.h"

namespace Engine::UI
{
    class GameObjectEditor;
    class GameObjectEditorUI final: public EditorUI
    {
        friend class GameObjectEditor;

    private:
        GameObjectEditorUI(GameObjectEditor *const editor);
        GameObjectEditorUI(const GameObjectEditorUI &rhs) = delete;
        GameObjectEditorUI(GameObjectEditorUI &&rhs) noexcept = delete;
        GameObjectEditorUI &operator=(const GameObjectEditorUI &rhs) = delete;
        GameObjectEditorUI &operator=(GameObjectEditorUI &&rhs) noexcept = delete;
        ~GameObjectEditorUI();

    protected:
        void UpdateInner() override final;
    };
}