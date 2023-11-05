#include <GL/glew.h>
#include "Engine/Essentials/Scripts/Visuals/CameraScript.h"

namespace Engine::Scripts
{
    CameraScript::CameraScript(Objects::GameObject *object, Graphics::VirtualCamera *camera)
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

    Graphics::VirtualCamera *const CameraScript::GetCamera()
    {
        return camera;
    }

    Tools::Interfaces::IClonable *CameraScript::Clone()
    {
        return new CameraScript(*this);
    }

    void CameraScript::UpdateInner()
    {
        camera->SetPosition(GetGameObject()->GetTransform().GetPosition());
        camera->SetDirection(GetGameObject()->GetTransform().GetForwardDirection());
        camera->SetUp(GetGameObject()->GetTransform().GetUpDirection());
    }

    void CameraScript::UpdateEditor()
    {
        camera->SetPosition(GetGameObject()->GetTransform().GetPosition());
        camera->SetDirection(GetGameObject()->GetTransform().GetForwardDirection());
        camera->SetUp(GetGameObject()->GetTransform().GetUpDirection());
    }

    void CameraScript::SelectEditor()
    {}

    void CameraScript::DeselectEditor()
    {}


    size_t CameraScript::GetDefaultPriority() const
    {
        return priority;
    }
}