#pragma once

#include "Engine/UI/Editor/Editor.h"
#include "Engine/UI/Editor/EditorUI.h"
#include "Engine/UI/Editor/EditorContainer.h"

namespace Engine::UI
{
    class GameObjectEditor final: public Editor
    {
        friend class EditorContainer;

    private:
        GameObjectEditor();
        GameObjectEditor(const GameObjectEditor &rhs) = delete;
        GameObjectEditor(GameObjectEditor &&rhs) noexcept = delete;
        GameObjectEditor &operator=(const GameObjectEditor &rhs) = delete;
        GameObjectEditor &operator=(GameObjectEditor &&rhs) noexcept = delete;
        ~GameObjectEditor();

    public:
        size_t GetDefaultPriority() const override final;
        std::type_index GetScriptType() const override final;

    protected:
        void UpdateFromTarget() override final;
        void UpdateFromUI() override final;

    public:
        const std::string &GetTargetName() const;

    public:
        bool *GetIsActive();
        float *GetPosition();
        float *GetRotation();
        float *GetScale();

    private:
        glm::vec3 bufferPosition;
        glm::vec3 bufferRotation;
        glm::vec3 bufferScale;

    private:
        float position[3];
        float rotation[3];
        float scale[3];
        bool isActive;

    private:
        static const size_t priority;
    };
}