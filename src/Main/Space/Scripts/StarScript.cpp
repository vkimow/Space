#include "Space/Scripts/StarScript.h"
#include "Engine/Graphics/Light/LightSource.h"

namespace Main::Space
{
    StarScript::StarScript(Engine::Objects::GameObject *object, SpaceManager *space, Engine::GraphicsModule *graphics)
        : Script(object)
        , space(space)
        , graphics(graphics)
        , celestialBodyScript(nullptr)
        , lightSourceScript(nullptr)
    {
        SerializeScripts(object);
    }

    StarScript::StarScript(const StarScript & rhs)
        : Script(rhs)
        , space(rhs.space)
        , graphics(rhs.graphics)
        , celestialBodyScript(nullptr)
        , lightSourceScript(nullptr)
    {}

    StarScript::StarScript(StarScript && rhs) noexcept
        : Script(std::move(rhs))
        , space(rhs.space)
        , graphics(rhs.graphics)
        , celestialBodyScript(nullptr)
        , lightSourceScript(nullptr)
    {}

    StarScript &StarScript::operator=(const StarScript & rhs)
    {
        Script::operator=(rhs);
        return *this;
    }

    StarScript &StarScript::operator=(StarScript &&rhs) noexcept
    {
        Script::operator=(std::move(rhs));
        return *this;
    }

    StarScript::~StarScript()
    {}

    Engine::Tools::Interfaces::IClonable *StarScript::Clone()
    {
        return new StarScript(*this);
    }

    void StarScript::UpdateInner()
    {}

    void StarScript::UpdateEditor()
    {}

    void StarScript::SetGameObject(Engine::Objects::GameObject *value)
    {
        Script::SetGameObject(value);
        SerializeScripts(value);
    }

    void StarScript::OnEnabledInner()
    {
        lightSourceScript->SetActive(true);
    }

    void StarScript::OnDisabledInner()
    {
        lightSourceScript->SetActive(false);
    }

    size_t StarScript::GetDefaultPriority() const
    {
        return priority;
    }

    void StarScript::SerializeScripts(Engine::Objects::GameObject *object)
    {
        CelestialBodyScript *newCelestialBodyScript;
        Engine::Scripts::LightSourceScript *newLightSourceScript;
        if (!object->ConstainsScript<CelestialBodyScript>())
        {
            newCelestialBodyScript = object->EmplaceScript<CelestialBodyScript>(space, graphics);
        }
        else
        {
            newCelestialBodyScript = object->GetScript<CelestialBodyScript>();
        }

        if (!object->ConstainsScript<Engine::Scripts::LightSourceScript>())
        {
            newLightSourceScript = object->EmplaceScript<Engine::Scripts::LightSourceScript>(graphics->GetLightManager(), Engine::Graphics::LightSourceType::PointLight);
        }
        else
        {
            newLightSourceScript = object->GetScript<Engine::Scripts::LightSourceScript>();
        }

        if (newCelestialBodyScript == celestialBodyScript && newLightSourceScript == lightSourceScript)
        {
            return;
        }
        if (celestialBodyScript && lightSourceScript)
        {
            celestialBodyScript->RemoveListenerOnRadiusChanged(lightSourceScript->setRadius);
        }
        celestialBodyScript = newCelestialBodyScript;
        lightSourceScript = newLightSourceScript;
        celestialBodyScript->AddListenerOnRadiusChanged(lightSourceScript->setRadius);
        lightSourceScript->GetLightSource()->GetAmbient().SetIntensity(0.0f);
        lightSourceScript->GetLightSource()->SetType(Engine::Graphics::LightSourceType::PointLight);
        lightSourceScript->GetLightSource()->GetAttenuation().SetQuadratic(0.0f);
        lightSourceScript->GetLightSource()->GetAttenuation().SetLinear(0.0f);
    }
}
