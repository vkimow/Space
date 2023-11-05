#pragma once

#include "Engine/UI/Buffer.h"
#include "Engine/UI/Editor/Editor.h"
#include "Engine/UI/Editor/EditorUI.h"
#include "Engine/UI/Editor/EditorContainer.h"

namespace Engine::UI
{
    class RenderEditor final: public Editor
    {
        friend class EditorContainer;

    private:
        RenderEditor();
        RenderEditor(const RenderEditor &rhs) = delete;
        RenderEditor(RenderEditor &&rhs) noexcept = delete;
        RenderEditor &operator=(const RenderEditor &rhs) = delete;
        RenderEditor &operator=(RenderEditor &&rhs) noexcept = delete;
        ~RenderEditor();

    public:
        size_t GetDefaultPriority() const override final;
        std::type_index GetScriptType() const override final;

    protected:
        void UpdateFromTarget() override final;
        void UpdateFromUI() override final;

    private:
        static const size_t priority;
    };
}