#pragma once

#include <string>
#include "Engine/Objects/GameObject.h"

namespace Engine
{
    class Window;
    class Modules;
    class GraphicsModule;
    class TimeModule;
    class InputModule;

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

    private:
        const size_t id;
        const std::string name;
        ::Engine::Window *const window;
        ::Engine::Modules *const modules;

    public:
        size_t GetId() const;
        const std::string &GetName() const;

    protected:
        ::Engine::Modules *const GetModules() const;
        ::Engine::Window *const GetWindow() const;


    protected:
        template<typename Object = GameObject, typename... Args, typename = std::enable_if_t<std::is_base_of_v<GameObject, Object>>>
        Object *CreateGameObject(const std::string &name, Args&&... args)
        {
            Object *object = new Object(name, std::forward<Args>(args)...);
            objects.insert(std::make_pair(name, object));
            return object;
        }

        template<typename Object = GameObject, typename = std::enable_if_t<std::is_base_of_v<GameObject, Object>>>
        Object *CreateGameObject(const std::string &name)
        {
            Object *object = new Object(name);
            objects.insert(std::make_pair(name, object));
            return object;
        }

        void UpdateGameObject(const std::string &name);
        GameObject *GetGameObject(const std::string &name);
        bool ContainsGameObjects(GameObject *object);
        void RemoveGameObject(GameObject *object);
        void ClearObjects();

    private:
        std::unordered_map<std::string, GameObject *> objects;

    private:
        static size_t idCounter;
    };
}