#pragma once

#include <string>
#include "Engine/Objects/GameObject.h"

namespace Engine
{
    class Window;
    class Modules;
}

namespace Engine::Objects
{
    class Scene
    {
    public:
        Scene(const std::string &name, ::Engine::Window *const window, ::Engine::Modules *const modules);

        Scene(const Scene &rhs) = delete;
        Scene(Scene &&rhs) noexcept = delete;
        Scene &operator=(const Scene &rhs) = delete;
        Scene &operator=(Scene &&rhs) noexcept = delete;

        virtual ~Scene();

    public:
        virtual void Update() = 0;
        virtual void Render() = 0;

    protected:
        size_t id;
        std::string name;
        ::Engine::Window *const window;
        ::Engine::Modules *const modules;

    public:
        template<typename Object = GameObject, typename... Args, typename = std::enable_if_t<std::is_base_of_v<GameObject, Object>>>
        void CreateGameObject(const std::string& name, Args&&... args)
        {
            Object *object = new Object(name, std::forward<Args>(args)...);
            objects.insert(std::make_pair(name, object));
        }

        template<typename Object = GameObject, typename = std::enable_if_t<std::is_base_of_v<GameObject, Object>>>
        void CreateGameObject(const std::string &name)
        {
            Object *object = new Object(name);
            objects.insert(std::make_pair(name, object));
        }

        GameObject* GetGameObject(const std::string &name);
        bool ContainsGameObjects(GameObject *object);
        void RemoveGameObject(GameObject *object);
        void ClearObjects();

    private:
        std::unordered_map<std::string, GameObject *> objects;

    private:
        static size_t idCounter;
    };
}