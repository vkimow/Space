#pragma once
#include "Engine/UI/Menu/Menu.h"
#include "Engine/UI/Menu/MenuContainer.h"
#include "Engine/Objects/Scene.h"
#include "Engine/UI/Editor/EditorManager.h"
#include "Engine/Graphics/Light/LightManager.h"
#include "Engine/UI/Buffer.h"

namespace Engine::UI
{
    class GlobalLightingMenu final: public Menu
    {
        friend class MenuContainer;

    private:
        GlobalLightingMenu(Graphics::LightManager *lightManager);
        GlobalLightingMenu(const GlobalLightingMenu &rhs) = delete;
        GlobalLightingMenu(GlobalLightingMenu &&rhs) noexcept = delete;
        GlobalLightingMenu &operator=(const GlobalLightingMenu &rhs) = delete;
        GlobalLightingMenu &operator=(GlobalLightingMenu &&rhs) noexcept = delete;
        ~GlobalLightingMenu();

    public:
        void Update() override final;
        size_t GetDefaultPriority() const override final;

    private:
        void UpdateFromTarget();
        void UpdateFromUI();

    public:
        Buffer<bool> &GetIsAmbientEnabled();
        Buffer<Graphics::LightValue> &GetAmbientLight();

        Buffer<bool> &GetIsDirectionalEnabled();
        Buffer<glm::vec3> &GetDirectionalDirection();
        Buffer<Graphics::LightValue> &GetDirectionalDiffuse();
        Buffer<Graphics::LightValue> &GetDirectionalSpecular();

    private:
        Buffer<bool> isAmbientEnabled;
        Buffer<Graphics::LightValue> ambientLight;

        Buffer<bool> isDirectionalEnabled;
        Buffer<Graphics::LightValue> directionalDiffuse;
        Buffer<Graphics::LightValue> directionalSpecular;
        Buffer<glm::vec3> directionalDirection;

    private:
        Graphics::LightManager *const lightManager;

    private:
        static const size_t priority;
    };
}