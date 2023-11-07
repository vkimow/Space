#pragma once

#include "Engine/UI/Buffer.h"
#include "Engine/UI/Editor/Editor.h"
#include "Engine/UI/Editor/EditorUI.h"
#include "Engine/UI/Editor/EditorContainer.h"
#include "Engine/Essentials/Scripts/Visuals/LightSourceScript.h"
#include "Engine/Graphics/Light/LightSourceType.h"
#include "Engine/Graphics/Light/LightValue.h"
#include "Engine/Graphics/Light/LightAttenuation.h"

namespace Engine::UI
{
    class LightSourceEditor final: public Editor
    {
        friend class EditorContainer;

    private:
        LightSourceEditor();
        LightSourceEditor(const LightSourceEditor &rhs) = delete;
        LightSourceEditor(LightSourceEditor &&rhs) noexcept = delete;
        LightSourceEditor &operator=(const LightSourceEditor &rhs) = delete;
        LightSourceEditor &operator=(LightSourceEditor &&rhs) noexcept = delete;
        ~LightSourceEditor();

    public:
        size_t GetDefaultPriority() const override final;
        std::type_index GetScriptType() const override final;

    protected:
        void UpdateFromTarget() override final;
        void UpdateFromUI() override final;

    public:
        Buffer<Graphics::LightSourceType> &GetType();
        Buffer<Graphics::LightValue> &GetAmbient();
        Buffer<Graphics::LightValue> &GetDiffuse();
        Buffer<Graphics::LightValue> &GetSpecular();
        Buffer<Graphics::LightAttenuation> &GetAttenuation();
        Buffer<float> &GetAngle();
        Buffer<float> &GetRadius();

    private:
        Buffer<Graphics::LightSourceType> type;
        Buffer<Graphics::LightValue> ambient;
        Buffer<Graphics::LightValue> diffuse;
        Buffer<Graphics::LightValue> specular;
        Buffer<Graphics::LightAttenuation> attenuation;
        Buffer<float> angle;
        Buffer<float> radius;

    private:
        static const size_t priority;
    };
}