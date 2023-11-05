#pragma once

#include "Engine/UI/Editor/EditorUI.h"

namespace Main::Space
{
    class CelestialBodyEditor;
    class CelestialBodyEditorUI final: public Engine::UI::EditorUI
    {
        friend class CelestialBodyEditor;

    private:
        CelestialBodyEditorUI(CelestialBodyEditor *const editor);
        CelestialBodyEditorUI(const CelestialBodyEditorUI &rhs) = delete;
        CelestialBodyEditorUI(CelestialBodyEditorUI &&rhs) noexcept = delete;
        CelestialBodyEditorUI &operator=(const CelestialBodyEditorUI &rhs) = delete;
        CelestialBodyEditorUI &operator=(CelestialBodyEditorUI &&rhs) noexcept = delete;
        ~CelestialBodyEditorUI() = default;

    protected:
        void UpdateInner() override final;
    };
}