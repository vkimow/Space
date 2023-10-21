#pragma once
#include "Engine/Objects/Script.h"
#include "Engine/Objects/GameObject.h"
#include "Engine/Graphics/Camera/Camera.h"
#include "Engine/Graphics/Camera/CameraManager.h"

namespace Game::Scripts
{
    class CameraScript final: public Engine::Objects::Script
    {
    public:
        CameraScript(Engine::Objects::GameObject *object, Engine::Graphics::Camera *camera);
        CameraScript(const CameraScript &rhs);
        CameraScript(CameraScript &&rhs) noexcept;

        CameraScript &operator=(const CameraScript &rhs);
        CameraScript &operator=(CameraScript &&rhs) noexcept;

        ~CameraScript() = default;

    public:
        Engine::Graphics::Camera *const GetCamera();

    private:
        Engine::Graphics::Camera *camera;

    protected:
        Engine::Objects::Script *Clone() noexcept override final;

    protected:
        void UpdateInner() override final;
        size_t GetDefaultPriority() const override final;

    private:
        const static size_t priority;
    };
}