#pragma once

#include <type_traits>
#include <typeindex>
#include "Engine/Objects/Script.h"
#include "Engine/Objects/GameObject.h"
#include "Engine/UI/Buffer.h"
#include <unordered_set>

namespace Engine::UI
{
    class EditorUI;

    class Editor
    {
        friend class EditorContainer;
        friend class EditorManager;
        friend class EditorUI;

    protected:
        Editor(const std::string &name, EditorUI *const ui, bool scriptCanBeDisactivated = true);
        Editor(const Editor &rhs) = delete;
        Editor(Editor &&rhs) noexcept = delete;
        Editor &operator=(const Editor &rhs) = delete;
        Editor &operator=(Editor &&rhs) noexcept = delete;

    public:
        virtual ~Editor();

    protected:
        void Update();
        void SetTarget(Objects::GameObject *const object);

    public:
        Objects::GameObject *const GetTarget() const;

    public:
        void SetActive(bool value);
        bool IsActive() const;

    public:
        const std::string &GetName() const;
        virtual size_t GetDefaultPriority() const = 0;
        virtual std::type_index GetScriptType() const = 0;
        virtual const std::unordered_set<std::type_index> *const EditorsToDisable() const { return nullptr; };

    protected:
        virtual void UpdateFromTarget() = 0;
        virtual void UpdateFromUI() = 0;

    protected:
        template<typename EUI, typename = std::enable_if_t<std::is_base_of_v<EditorUI, EUI>>>
        EUI *const GetUI() { return static_cast<EUI *const>(ui); }
        template<typename S = Objects::Script, typename = std::enable_if_t<std::is_base_of_v<Objects::Script, S>>>
        S *const GetScriptFromTarget() { return target->GetScript<S>(); }
        template<typename S = Objects::Script, typename = std::enable_if_t<std::is_base_of_v<Objects::Script, S>>>
        S *const BufferTargetScript() { targetScript = target->GetScript<S>(); return GetTargetScript<S>(); }
        template<typename S = Objects::Script, typename = std::enable_if_t<std::is_base_of_v<Objects::Script, S>>>
        S *const GetTargetScript() const { return static_cast<S*>(targetScript); }

    private:
        const std::string name;
        bool isActive;
        EditorUI *const ui;
        Objects::GameObject *target;
        Objects::Script *targetScript;

    private:
        Buffer<bool> isScriptActive;
        bool scriptCanBeDisactivated;
    };
}