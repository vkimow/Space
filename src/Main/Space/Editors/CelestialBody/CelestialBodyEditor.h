#pragma once
#include "Engine/UI/Buffer.h"
#include "Engine/UI/Editor/Editor.h"
#include "Engine/UI/Editor/EditorContainer.h"

namespace Main::Space
{
    class CelestialBodyScript;
    class CelestialBodyEditor final: public Engine::UI::Editor
    {
        friend class Engine::UI::EditorContainer;
        friend class CelestialBodyEditorUI;

    private:
        CelestialBodyEditor();
        CelestialBodyEditor(const CelestialBodyEditor &rhs) = delete;
        CelestialBodyEditor(CelestialBodyEditor &&rhs) noexcept = delete;
        CelestialBodyEditor &operator=(const CelestialBodyEditor &rhs) = delete;
        CelestialBodyEditor &operator=(CelestialBodyEditor &&rhs) noexcept = delete;
        ~CelestialBodyEditor();

    public:
        size_t GetDefaultPriority() const override final;
        std::type_index GetScriptType() const override final;
        const std::unordered_set<std::type_index> *const EditorsToDisable() const override final;

    protected:
        void UpdateFromTarget() override final;
        void UpdateFromUI() override final;

    private:
        Engine::UI::Buffer<glm::vec3> position;
        Engine::UI::Buffer<float> mass;
        Engine::UI::Buffer<float> radius;
        Engine::UI::Buffer<glm::vec3> velocity;

    private:
        static size_t priority;
        static const std::unordered_set<std::type_index> editorsToDisable;
    };
}