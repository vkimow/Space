#include "Engine/Essentials/Scripts/Visuals/LightSourceScript.h"
#include "Engine/Graphics/Light/LightSource.h"
#include "Engine/Graphics/Light/LightManager.h"
#include "Engine/Objects/Transform.h"
#include "Engine/Objects/GameObject.h"

namespace Engine::Scripts
{
    LightSourceScript::LightSourceScript(Objects::GameObject *object, Graphics::LightManager *lightManager, Graphics::LightSourceType lightSourceType)
        : Script(object)
        , lightManager(lightManager)
        , lightSource(lightManager->GetContainer().CreateLightSource())
        , setRadius(this, &LightSourceScript::SetRadius)
    {
        lightSource->SetTransform(GetGameObject()->GetTransformPtr());
        SetDefaultLightSource(lightSourceType);
    }

    LightSourceScript::LightSourceScript(const LightSourceScript &rhs)
        : Script(rhs)
        , lightManager(rhs.lightManager)
        , lightSource(new Graphics::LightSource(*rhs.lightSource))
        , setRadius(this, &LightSourceScript::SetRadius)
    {
        lightManager->GetContainer().AddLightSource(lightSource);
    }

    LightSourceScript::LightSourceScript(LightSourceScript && rhs) noexcept
        : Script(std::move(rhs))
        , lightManager(rhs.lightManager)
        , lightSource(rhs.lightSource)
        , setRadius(this, &LightSourceScript::SetRadius)
    {
        rhs.lightSource = nullptr;
    }

    LightSourceScript &LightSourceScript::operator=(const LightSourceScript & rhs)
    {
        Script::operator=(rhs);
        lightManager = rhs.lightManager;
        ClearLightSource();
        lightSource = new Graphics::LightSource(*rhs.lightSource);
        lightManager->GetContainer().AddLightSource(lightSource);
        return *this;
    }

    LightSourceScript &LightSourceScript::operator=(LightSourceScript &&rhs) noexcept
    {
        Script::operator=(std::move(rhs));
        lightManager = rhs.lightManager;
        ClearLightSource();
        lightSource = rhs.lightSource;
        rhs.lightSource = nullptr;
        return *this;
    }

    LightSourceScript::~LightSourceScript()
    {
        ClearLightSource();
    }

    Tools::Interfaces::IClonable *LightSourceScript::Clone()
    {
        return new LightSourceScript(*this);
    }

    void LightSourceScript::SetGameObject(Objects::GameObject *value)
    {
        Script::SetGameObject(value);
        lightSource->SetTransform(value->GetTransformPtr());
    }

    void LightSourceScript::OnEnabledInner()
    {
        lightSource->SetActive(true);
        LOG_DEBUG("Light is enabled");
    }

    void LightSourceScript::OnDisabledInner()
    {
        lightSource->SetActive(false);
        LOG_DEBUG("Light is disabled");
    }

    void LightSourceScript::UpdateInner()
    {}

    void LightSourceScript::UpdateEditor()
    {}

    void LightSourceScript::SelectEditor()
    {}

    void LightSourceScript::DeselectEditor()
    {}

    void LightSourceScript::ClearLightSource()
    {
        if (lightSource)
        {
            lightManager->GetContainer().RemoveLightSource(lightSource);
            lightSource = nullptr;
        }
    }

    void LightSourceScript::SetDefaultLightSource(Graphics::LightSourceType value)
    {
        lightSource->SetType(value);
        switch (value)
        {
            case Graphics::LightSourceType::PointLight:
            {
                break;
            }
            case Graphics::LightSourceType::SpotLight:
            {
                lightSource->SetAngleInDegrees(45.0f);
                break;
            }
            default:
            {
                LOG_ERROR("This type of light source isn't supported");
                break;
            }
        }
    }

    Graphics::LightSource *const LightSourceScript::GetLightSource() const
    {
        return lightSource;
    }

    size_t LightSourceScript::GetDefaultPriority() const
    {
        return priority;
    }

    void LightSourceScript::SetRadius(float value)
    {
        lightSource->SetRadius(value);
    }
}