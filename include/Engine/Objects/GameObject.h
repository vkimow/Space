#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include <unordered_map>
#include "Engine/Objects/Script.h"
#include "Engine/Objects/Transform.h"
#include <type_traits>
#include <typeinfo>
#include <typeindex>
#include "Engine/Tools/Log/Logger.h"
#include "Engine/Tools/Structs/TypeMapWithPriority.h"

namespace Engine::Objects
{
    class GameObject final
    {
    private:
        struct ScriptInner
        {
            std::type_index type;
            Script *script;
            size_t priority;
        };

        friend class Scene;
        using ScriptsContainer = Tools::Structs::TypeMapWithPriority<Script>;

    public:
        GameObject();
        GameObject(const std::string &name);
        GameObject(const std::string &name, const Transform &transform);
        GameObject(const std::string &name, Transform &&transform);

        GameObject(const GameObject &rhs) noexcept;
        GameObject(GameObject &&rhs) noexcept;

        GameObject &operator=(const GameObject &rhs);
        GameObject &operator=(GameObject &&rhs) noexcept;

        ~GameObject();

    public:
        const std::string &GetName() const;
        Transform &GetTransform();
        Transform *const GetTransformPtr();
        const Transform &GetTransform() const;
        const Transform *const GetTransformPtr() const;
        const ScriptsContainer &GetScripts() const;
        bool IsActive() const;
        bool IsInvisible() const;

    public:
        void SetActive(bool value);
        void SetInvisible(bool value);

    public:
        template<typename S, typename... Args, typename = std::enable_if_t<std::is_base_of_v<Script, S>>>
        S *const EmplaceScript(Args&&... args)
        {
            S *script = new S(this, std::forward<Args>(args)...);
            scripts.Add(script);
            return script;
        }

        template<typename S, typename = std::enable_if_t<std::is_base_of_v<Script, S>>>
        S *const EmplaceScript()
        {
            S *script = new S(this);
            scripts.Add(script);
            return script;
        }

        template<typename S, typename = std::enable_if_t<std::is_base_of_v<Script, S>>>
        void AddScript(S *script)
        {
            if (!script)
            {
                LOG_ERROR("Script is null");
                return;
            }

            Script *basePointer = static_cast<Script *>(script);
            if (basePointer->object)
            {
                LOG_ERROR("Script already has an owner");
                return;
            }
            basePointer->SetGameObject(this);
            scripts.Add(script);
        }

        template<typename S, typename = std::enable_if_t<std::is_base_of_v<Script, S>>>
        bool ConstainsScript()
        {
            return scripts.Contains<S>();
        }

        template<typename S, typename = std::enable_if_t<std::is_base_of_v<Script, S>>>
        void RemoveScript()
        {
            scripts.Remove<S>();
        }

        template<typename S, typename = std::enable_if_t<std::is_base_of_v<Script, S>>>
        size_t const GetScriptPriority()
        {
            return scripts.GetPriority<S>();
        }

        template<typename S, typename = std::enable_if_t<std::is_base_of_v<Script, S>>>
        size_t const GetScriptCallOrder()
        {
            return scripts.GetOrder<S>();
        }

        template<typename S, typename = std::enable_if_t<std::is_base_of_v<Script, S>>>
        S *const GetScript()
        {
            return scripts.Get<S>();
        }

        template<typename S, typename = std::enable_if_t<std::is_base_of_v<Script, S>>>
        void SetScriptPriority(size_t priority)
        {
            scripts.SetPriority<S>(priority);
        }

    public:
        void Update();

    public:
        void UpdateEditor();
        void SelectEditor();
        void DeselectEditor();

    private:
        bool isActive;
        bool isInvisible;
        Transform tranform;
        std::string name;

    private:
        ScriptsContainer scripts;

    };
}