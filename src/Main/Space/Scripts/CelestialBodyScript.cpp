#include "Space/Scripts/CelestialBodyScript.h"
#include "Space/SpaceManager.h"

namespace Main::Space
{
    CelestialBodyScript::CelestialBodyScript(Engine::Objects::GameObject *object, SpaceManager *space, Engine::GraphicsModule *graphics)
        : CelestialBodyScript(object, 100.0f, 5.0f, glm::vec3(0.0f), space, graphics)
    {}

    CelestialBodyScript::CelestialBodyScript(Engine::Objects::GameObject *object, float mass, float radius, const glm::vec3 &velocity, SpaceManager *space, Engine::GraphicsModule *graphics)
        : Script(object)
        , mass(mass)
        , radius(0.0f)
        , velocity(velocity)
        , space(space)
        , graphics(graphics)
    {
        SetRadius(radius);
        space->AddCelestialBody(this);
    }

    CelestialBodyScript::CelestialBodyScript(const CelestialBodyScript &rhs)
        : Script(rhs)
        , mass(rhs.mass)
        , radius(rhs.radius)
        , velocity(rhs.velocity)
        , space(rhs.space)
        , graphics(rhs.graphics)
    {
        space->AddCelestialBody(this);
    }

    CelestialBodyScript::CelestialBodyScript(CelestialBodyScript &&rhs) noexcept
        : Script(std::move(rhs))
        , mass(rhs.mass)
        , radius(rhs.radius)
        , velocity(std::move(rhs.velocity))
        , space(rhs.space)
        , graphics(rhs.graphics)
    {
        space->AddCelestialBody(this);
    }

    CelestialBodyScript &CelestialBodyScript::operator=(const CelestialBodyScript &rhs)
    {
        Script::operator=(rhs);
        mass = rhs.mass;
        radius = rhs.radius;
        velocity = rhs.velocity;
        return *this;
    }

    CelestialBodyScript &CelestialBodyScript::operator=(CelestialBodyScript &&rhs) noexcept
    {
        Script::operator=(std::move(rhs));
        mass = rhs.mass;
        radius = rhs.radius;
        velocity = std::move(rhs.velocity);
        return *this;
    }

    CelestialBodyScript::~CelestialBodyScript()
    {
        space->RemoveCelestialBody(this);
    }

    Engine::Tools::Interfaces::IClonable *CelestialBodyScript::Clone()
    {
        return new CelestialBodyScript(*this);
    }

    void CelestialBodyScript::UpdateInner()
    {
    }

    void CelestialBodyScript::UpdateEditor()
    {
        std::string lineName = "Editor_CelestialBody_Line_" + GetGameObject()->GetName();
        auto &paths = space->GetGravitySimulation().GetPath(this);
        graphics->GetContainer()->AddLine(lineName, paths);
        auto renderUnit = graphics->GetRenderManager()->GetUnitBuilder().Create("MainShader", lineName.c_str(), "Orange", nullptr, GetGameObject()->GetTransform().GetPositionRotationMatrix());
        graphics->GetRenderManager()->GetPool().AddRenderUnit(renderUnit);
    }

    size_t CelestialBodyScript::GetDefaultPriority() const
    {
        return priority;
    }

    void CelestialBodyScript::ApplyAcceleration(const glm::vec3 &acceleration)
    {
        velocity += acceleration * space->GetTime().GetDeltaTime();
        GetTransform().Move(velocity * space->GetTime().GetDeltaTime());
    }

    void CelestialBodyScript::SetMass(float value)
    {
        mass = value;
    }

    void CelestialBodyScript::SetRadius(float value)
    {
        radius = value;
        constexpr float multiplier = 1.0f;
        GetTransform().SetScale(glm::vec3(value) * multiplier);
        OnRadiusChanged(value);
    }

    void CelestialBodyScript::SetVelocity(const glm::vec3 &value)
    {
        velocity = value;
    }

    float CelestialBodyScript::GetMass() const
    {
        return mass;
    }

    float CelestialBodyScript::GetRadius() const
    {
        return radius;
    }

    const glm::vec3 &CelestialBodyScript::GetVelocity() const
    {
        return velocity;
    }
}