#pragma once
#include "Engine/UI/Buffer.h"
#include "Engine/UI/Editor/Editor.h"
#include "Engine/UI/Editor/EditorContainer.h"
#include "Engine/Graphics/Light/LightValue.h"

namespace Main::Space
{
    class StarScript;
    class StarEditor final: public Engine::UI::Editor
    {
        friend class Engine::UI::EditorContainer;
        friend class StarEditorUI;

    private:
        StarEditor();
        StarEditor(const StarEditor &rhs) = delete;
        StarEditor(StarEditor &&rhs) noexcept = delete;
        StarEditor &operator=(const StarEditor &rhs) = delete;
        StarEditor &operator=(StarEditor &&rhs) noexcept = delete;
        ~StarEditor();

    public:
        size_t GetDefaultPriority() const override final;
        std::type_index GetScriptType() const override final;
        const std::unordered_set<std::type_index> *const EditorsToDisable() const override final;

    protected:
        void UpdateFromTarget() override final;
        void UpdateFromUI() override final;

    private:
        Engine::UI::Buffer<Engine::Graphics::LightValue> diffuse;
        Engine::UI::Buffer<Engine::Graphics::LightValue> specular;

    private:
        static size_t priority;
        static const std::unordered_set<std::type_index> editorsToDisable;
    };
}