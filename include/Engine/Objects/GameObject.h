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

    public:
        std::string &GetName();
        Transform &GetTransform();

    public:
        template<typename S, typename... Args, typename = std::enable_if_t<std::is_base_of_v<Script, S>>>
        void AddScript(Args&&... args)
        {
            S *script = new S(std::forward<Args>(args)...);
            std::type_index type = std::type_index(typeid(S));
            scripts.insert(std::make_pair(std::move(type), script));
        }

        template<typename S, typename = std::enable_if_t<std::is_base_of_v<Script, S>>>
        void AddScript()
        {
            S *script = new S();
            std::type_index type = std::type_index(typeid(S));
            scripts.insert(std::make_pair(std::move(type), script));
        }

        template<typename S, typename = std::enable_if_t<std::is_base_of_v<Script, S>>>
        void AddScript(S *script)
        {
            if (!script)
            {
                Engine::Tools::Logger::GetInstance()->GetLogger()->error("File:{}, Line:{} Script is null", "C:\\Creativity\\Programing\\Personal\\CPP\\Space\\include\\Engine\\Objects\\GameObject.h", 57);
                return;
            }
            std::type_index type = std::type_index(typeid(S));
            scripts.insert(std::make_pair(std::move(type), script));

        }

        template<typename S, typename = std::enable_if_t<std::is_base_of_v<Script, S>>>
        void ConstainsScript()
        {
            std::type_index type = std::type_index(typeid(S));
            return scripts.contains(std::move(type));
        }

        template<typename S, typename = std::enable_if_t<std::is_base_of_v<Script, S>>>
        void RemoveScript()
        {
            std::type_index type = std::type_index(typeid(S));
            scripts.erase(std::move(type));
        }

        template<typename S, typename = std::enable_if_t<std::is_base_of_v<Script, S>>>
        S *const GetScript()
        {
            std::type_index type = std::type_index(typeid(S));
            return static_cast<S>(scripts[std::move(type)]);
        }

    public:
        void ClearScripts();

    private:
        void DeleteScripts();

    private:
        virtual ~GameObject();

    private:
        virtual void Update();

    private:
        Transform tranform;
        std::string name;

    private:
        std::unordered_map<std::type_index, Script * > scripts;
    };
}