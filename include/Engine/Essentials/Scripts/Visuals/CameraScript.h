#pragma once
#include "Engine/Objects/Script.h"
#include "Engine/Objects/GameObject.h"
#include "Engine/Graphics/Camera/Camera.h"
#include "Engine/Graphics/Camera/CameraManager.h"

namespace Engine::Scripts
{
    class CameraScript final: public Objects::Script
    {
    public:
        CameraScript(Objects::GameObject *object, Graphics::Camera *camera);
        CameraScript(const CameraScript &rhs);
        CameraScript(CameraScript &&rhs) noexcept;

        CameraScript &operator=(const CameraScript &rhs);
        CameraScript &operator=(CameraScript &&rhs) noexcept;

        ~CameraScript() = default;

    public:
        Graphics::Camera *const GetCamera();

    private:
        Graphics::Camera *camera;

    protected:
        Tools::Interfaces::IClonable *Clone() override final;
        void UpdateInner() override final;

    public:
        size_t GetDefaultPriority() const override final;

    protected:
        void UpdateEditor() override final;
        void SelectEditor() override final;
        void DeselectEditor() override final;

    private:
        const static size_t priority;
    };
}