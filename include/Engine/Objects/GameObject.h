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

namespace Engine::Objects
{
    class GameObject
    {
    private:
        struct ScriptInner
        {
            std::type_index type;
            Script *script;
            size_t priority;
        };

        friend class Scene;

    protected:
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

    public:
        template<typename S, typename... Args, typename = std::enable_if_t<std::is_base_of_v<Script, S>>>
        void EmplaceScript(Args&&... args)
        {
            S *script = new S(this, std::forward<Args>(args)...);
            AddScriptInner<S>(script);
        }

        template<typename S, typename = std::enable_if_t<std::is_base_of_v<Script, S>>>
        void EmplaceScript()
        {
            S *script = new S(this);
            AddScriptInner<S>(script);
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
            basePointer->object = this;

            AddScriptInner<S>(script);
        }

    private:
        template<typename S, typename = std::enable_if_t<std::is_base_of_v<Script, S>>>
        void AddScriptInner(S *script)
        {
            AddScriptInner<S>(script, static_cast<Script *>(script)->GetDefaultPriority());
        }

        template<typename S, typename = std::enable_if_t<std::is_base_of_v<Script, S>>>
        void AddScriptInner(S *script, size_t priority)
        {
            std::type_index type = std::type_index(typeid(S));
            ScriptInner scriptInner(type, script, priority);

            auto pos = std::find_if(scripts.begin(), scripts.end(),
                [priority](const ScriptInner &scriptInner) { return scriptInner.priority > priority; }
            );

            size_t index = 0;
            if (pos == scripts.end())
            {
                scripts.push_back(std::move(scriptInner));
                index = scripts.size() - 1;
            }
            else
            {
                pos = scripts.insert(pos, std::move(scriptInner));
                index = pos - scripts.begin();
            }

            typeToIndex.insert(std::make_pair(std::move(type), index));
        }

        template<typename S, typename = std::enable_if_t<std::is_base_of_v<Script, S>>>
        ScriptInner &GetScriptInner()
        {
            size_t index = GetScriptIndex<S>();
            return scripts[index];
        }

        template<typename S, typename = std::enable_if_t<std::is_base_of_v<Script, S>>>
        size_t const GetScriptIndex()
        {
            std::type_index type = std::type_index(typeid(S));
            return typeToIndex[std::move(type)];
        }

    public:
        template<typename S, typename = std::enable_if_t<std::is_base_of_v<Script, S>>>
        void ConstainsScript()
        {
            std::type_index type = std::type_index(typeid(S));
            return typeToIndex.contains(std::move(type));
        }

        template<typename S, typename = std::enable_if_t<std::is_base_of_v<Script, S>>>
        void RemoveScript()
        {
            std::type_index type = std::type_index(typeid(S));
            size_t index = typeToIndex[type];
            ScriptInner &scriptInner = scripts[index];

            delete scriptInner.script;
            scripts.erase(&scriptInner);
            typeToIndex.erase(std::move(type));
            UpdateTypeToIndexByScripts(index);
        }

        template<typename S, typename = std::enable_if_t<std::is_base_of_v<Script, S>>>
        size_t const GetScriptPriority()
        {
            ScriptInner &scriptInner = GetScriptInner<S>();
            return scriptInner.priority;
        }

        template<typename S, typename = std::enable_if_t<std::is_base_of_v<Script, S>>>
        size_t const GetScriptCallOrder()
        {
            return GetScriptIndex<S>();
        }

        template<typename S, typename = std::enable_if_t<std::is_base_of_v<Script, S>>>
        S *const GetScript()
        {
            ScriptInner &scriptInner = GetScriptInner<S>();
            return static_cast<S *const>(scriptInner.script);
        }

        template<typename S, typename = std::enable_if_t<std::is_base_of_v<Script, S>>>
        void SetScriptPriority(size_t priority)
        {
            size_t index = GetScriptIndex<S>();
            ScriptInner &scriptInner = scripts[index];
            scriptInner.priority = priority;
            SortScriptsAfterPriorityChangeOfOneElement(index);
        }

    private:
        void UpdateTypeToIndexByScripts(size_t start);
        void SortScriptsAfterPriorityChangeOfOneElement(size_t start);

    public:
        void ClearScripts();

    private:
        void DeleteScripts();

    public:
        virtual void Update();

    private:
        Transform tranform;
        std::string name;

    private:
        std::vector<ScriptInner> scripts;
        std::unordered_map<std::type_index, size_t> typeToIndex;
    };
}