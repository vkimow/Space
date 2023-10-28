#pragma once

#include <type_traits>
#include <typeindex>
#include "Engine/Objects/Script.h"
#include "Engine/Objects/GameObject.h"

namespace Engine::UI
{
    class EditorUI;

    class Editor
    {
        friend class EditorContainer;
        friend class EditorManager;

    protected:
        Editor(const std::string& name, EditorUI *const ui);
        Editor(const Editor &rhs) = delete;
        Editor(Editor &&rhs) noexcept = delete;
        Editor &operator=(const Editor &rhs) = delete;
        Editor &operator=(Editor &&rhs) noexcept = delete;

    public:
        virtual ~Editor();
        
    private:
        void Update();
        void SetTarget(Objects::GameObject *const object);

    public:
        void SetActive(bool value);
        bool IsActive() const;

    public:
        const std::string& GetName() const;
        virtual size_t GetDefaultPriority() const = 0;
        virtual std::type_index GetScriptType() const = 0;

    protected:
        virtual void UpdateFromTarget() = 0;
        virtual void UpdateFromUI() = 0;

    protected:
        template<typename EUI, typename = std::enable_if_t<std::is_base_of_v<EditorUI, EUI>>>
        EUI *const GetUI() { return static_cast<EUI *const>(ui); }
        template<typename S, typename = std::enable_if_t<std::is_base_of_v<Objects::Script, S>>>
        S *const GetScriptFromTarget() { return target->GetScript<S>(); }
        Objects::GameObject *const GetTarget();
        const Objects::GameObject *const GetTarget() const;

    private:
        const std::string name;
        bool isActive;
        EditorUI *const ui;
        Objects::GameObject *target;
    };
}