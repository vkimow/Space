#include "Main/Scripts/CameraScript.h"

namespace Game::Scripts
{
    CameraScript::CameraScript(Engine::Objects::GameObject *object, Engine::Graphics::Camera *camera)
        : Script(object)
        , camera(camera)
    {}

    CameraScript::CameraScript(const CameraScript & rhs)
        : Script(rhs)
        , camera(rhs.camera)
    {}

    CameraScript::CameraScript(CameraScript && rhs) noexcept
        : Script(std::move(rhs))
        , camera(rhs.camera)
    {}

    CameraScript &CameraScript::operator=(const CameraScript & rhs)
    {
        Script::operator=(rhs);
        camera = rhs.camera;
        return *this;
    }

    CameraScript &CameraScript::operator=(CameraScript &&rhs) noexcept
    {
        Script::operator=(std::move(rhs));
        camera = rhs.camera;
        return *this;
    }

    Engine::Graphics::Camera *const CameraScript::GetCamera()
    {
        return camera;
    }

    Engine::Objects::Script *CameraScript::Clone() noexcept
    {
        return new CameraScript(*this);
    }

    void CameraScript::UpdateInner()
    {
        camera->SetPosition(object->GetTransform().GetPosition());
        camera->SetFront(object->GetTransform().GetForwardDirection());
        camera->SetUp(object->GetTransform().GetUpDirection());
    }

    size_t CameraScript::GetDefaultPriority() const
    {
        return priority;
    }
}