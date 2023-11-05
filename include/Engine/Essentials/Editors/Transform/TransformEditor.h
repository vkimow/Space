#pragma once

#include "Engine/UI/Buffer.h"
#include "Engine/UI/Editor/Editor.h"
#include "Engine/UI/Editor/EditorUI.h"
#include "Engine/UI/Editor/EditorContainer.h"

namespace Engine::UI
{
    class TransformEditor final: public Editor
    {
        friend class EditorContainer;

    private:
        TransformEditor();
        TransformEditor(const TransformEditor &rhs) = delete;
        TransformEditor(TransformEditor &&rhs) noexcept = delete;
        TransformEditor &operator=(const TransformEditor &rhs) = delete;
        TransformEditor &operator=(TransformEditor &&rhs) noexcept = delete;
        ~TransformEditor();

    public:
        size_t GetDefaultPriority() const override final;
        std::type_index GetScriptType() const override final;

    protected:
        void UpdateFromTarget() override final;
        void UpdateFromUI() override final;

    private:
        Buffer<glm::vec3> position;
        Buffer<glm::vec3> rotation;
        Buffer<glm::vec3> scale;

    public:
        Buffer<glm::vec3> &GetPosition();
        Buffer<glm::vec3> &GetRotation();
        Buffer<glm::vec3> &GetScale();

    private:
        static const size_t priority;
    };
}