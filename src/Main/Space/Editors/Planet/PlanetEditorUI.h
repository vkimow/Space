#pragma once

#include "Engine/UI/Editor/EditorUI.h"

namespace Main::Space
{
    class PlanetEditor;
    class PlanetEditorUI final: public Engine::UI::EditorUI
    {
        friend class PlanetEditor;

    private:
        PlanetEditorUI(PlanetEditor *const editor);
        PlanetEditorUI(const PlanetEditorUI &rhs) = delete;
        PlanetEditorUI(PlanetEditorUI &&rhs) noexcept = delete;
        PlanetEditorUI &operator=(const PlanetEditorUI &rhs) = delete;
        PlanetEditorUI &operator=(PlanetEditorUI &&rhs) noexcept = delete;
        ~PlanetEditorUI() = default;

    protected:
        void UpdateInner() override final;
    };
}