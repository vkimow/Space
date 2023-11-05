#pragma once

#include "Engine/Tools/Interfaces/IClonable.h"

namespace Engine::UI
{
    class Editor;
    class EditorUI;
}

namespace Engine::Objects
{
    class Transform;
    class GameObject;
    class Scene;

    class Script: public Tools::Interfaces::IClonable
    {
        friend class GameObject;
        friend class Scene;
        friend class UI::Editor;
        friend class UI::EditorUI;

    protected:
        Script();
        Script(GameObject *object);

        Script(const Script &rhs);
        Script(Script &&rhs) noexcept;

        Script &operator=(const Script &rhs);
        Script &operator=(Script &&rhs) noexcept;

    public:
        virtual ~Script() = default;

    public:
        bool IsActive() const;
        void SetActive(bool value);

    private:
        void OnEnabled();
        void OnDisabled();

    protected:
        virtual void OnEnabledInner() {};
        virtual void OnDisabledInner() {};

    private:
        void Update();

    protected:
        virtual void SetGameObject(GameObject *value);

    protected:
        virtual void UpdateInner() = 0;

    protected:
        virtual void UpdateEditor() {};
        virtual void SelectEditor() {};
        virtual void DeselectEditor() {};

    public:
        virtual size_t GetDefaultPriority() const = 0;
        GameObject *const GetGameObject() const;
        Transform &GetTransform();
        const Transform &GetTransform() const;

    private:
        bool isActive;
        bool isEnabled;
        GameObject *object;
    };
}