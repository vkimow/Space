#pragma once
#include "Engine/UI/Editor/Editor.h"
#include "Engine/UI/Editor/EditorContainer.h"

namespace Main::Space
{
    class PlanetEditor final: public Engine::UI::Editor
    {
        friend class Engine::UI::EditorContainer;
        friend class PlanetEditorUI;

    private:
        PlanetEditor();
        PlanetEditor(const PlanetEditor &rhs) = delete;
        PlanetEditor(PlanetEditor &&rhs) noexcept = delete;
        PlanetEditor &operator=(const PlanetEditor &rhs) = delete;
        PlanetEditor &operator=(PlanetEditor &&rhs) noexcept = delete;
        ~PlanetEditor();

    public:
        size_t GetDefaultPriority() const override final;
        std::type_index GetScriptType() const override final;

    protected:
        void UpdateFromTarget() override final;
        void UpdateFromUI() override final;

    private:
        static size_t priority;
    };
}