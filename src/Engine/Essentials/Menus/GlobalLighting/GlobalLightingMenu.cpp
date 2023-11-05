#include "Engine/Essentials/Menus/GlobalLighting/GlobalLightingMenu.h"
#include "Engine/Essentials/Menus/GlobalLighting/GlobalLightingMenuUI.h"

namespace Engine::UI
{
    GlobalLightingMenu::GlobalLightingMenu(Graphics::LightManager *lightManager)
        : Menu("GlobalLighting", new GlobalLightingMenuUI(this))
        , lightManager(lightManager)
    {}

    GlobalLightingMenu::~GlobalLightingMenu()
    {}

    void GlobalLightingMenu::Update()
    {
        UpdateFromTarget();
        UpdateUI();
        UpdateFromUI();
    }

    size_t GlobalLightingMenu::GetDefaultPriority() const
    {
        return priority;
    }

    void GlobalLightingMenu::UpdateFromTarget()
    {
        auto &container = lightManager->GetContainer();

        isAmbientEnabled = container.IsAmbientLightInitialized() && container.GetAmbientLight()->IsActive();
        if (isAmbientEnabled)
        {
            ambientLight = container.GetAmbientLight()->GetLight();
        }

        isDirectionalEnabled = container.IsDirectionalLightInitialized() && container.GetDirectionalLight()->IsActive();
        if (isDirectionalEnabled)
        {
            if (container.GetDirectionalLight()->GetDirection() != glm::normalize(directionalDirection.GetBuffer()))
            {
                directionalDirection = container.GetDirectionalLight()->GetDirection();
            }

            directionalDiffuse = container.GetDirectionalLight()->GetDiffuse();
            directionalSpecular = container.GetDirectionalLight()->GetSpecular();
        }
    }

    void GlobalLightingMenu::UpdateFromUI()
    {
        auto &container = lightManager->GetContainer();
        if (isAmbientEnabled.IsValueDiffersFromBuffer())
        {
            isAmbientEnabled.SetValueToBuffer();
            if (!container.IsAmbientLightInitialized())
            {
                container.InitializeAmbientLight();
            }

            container.GetAmbientLight()->SetActive(isAmbientEnabled);
        }

        if (isDirectionalEnabled.IsValueDiffersFromBuffer())
        {
            isDirectionalEnabled.SetValueToBuffer();
            if (!container.IsDirectionalLightInitialized())
            {
                container.InitializeDirectionalLight();
            }

            container.GetDirectionalLight()->SetActive(isDirectionalEnabled);
        }

        if (ambientLight.IsValueDiffersFromBuffer())
        {
            ambientLight.SetValueToBuffer();
            container.GetAmbientLight()->GetLight() = ambientLight;
        }

        if (directionalDirection.IsValueDiffersFromBuffer())
        {
            directionalDirection.SetValueToBuffer();
            container.GetDirectionalLight()->SetDirection(directionalDirection.GetBuffer());
        }

        if (directionalDiffuse.IsValueDiffersFromBuffer())
        {
            directionalDiffuse.SetValueToBuffer();
            container.GetDirectionalLight()->GetDiffuse() = directionalDiffuse;
        }

        if (directionalSpecular.IsValueDiffersFromBuffer())
        {
            directionalSpecular.SetValueToBuffer();
            container.GetDirectionalLight()->GetSpecular() = directionalSpecular;
        }
    }

    Buffer<bool> &GlobalLightingMenu::GetIsAmbientEnabled()
    {
        return isAmbientEnabled;
    }

    Buffer<Graphics::LightValue> &GlobalLightingMenu::GetAmbientLight()
    {
        return ambientLight;
    }

    Buffer<bool> &GlobalLightingMenu::GetIsDirectionalEnabled()
    {
        return isDirectionalEnabled;
    }

    Buffer<glm::vec3> &GlobalLightingMenu::GetDirectionalDirection()
    {
        return directionalDirection;
    }

    Buffer<Graphics::LightValue> &GlobalLightingMenu::GetDirectionalDiffuse()
    {
        return directionalDiffuse;
    }

    Buffer<Graphics::LightValue> &GlobalLightingMenu::GetDirectionalSpecular()
    {
        return directionalSpecular;
    }
}