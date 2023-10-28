#pragma once

#include <string>
#include "Engine/Objects/GameObject.h"

namespace Engine
{
    class Window;
    class GraphicsModule;
    class TimeModule;
    class InputModule;
    class UIModule;
}

namespace Engine::Objects
{
    class Scene
    {
    public:
        Scene(const std::string &name, ::Engine::Window *const window, ::Engine::TimeModule *const time, ::Engine::UIModule *const ui, ::Engine::InputModule *const input, ::Engine::GraphicsModule *const graphics);
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
        ::Engine::TimeModule *const time;
        ::Engine::UIModule *const ui;
        ::Engine::InputModule *const input;
        ::Engine::GraphicsModule *const graphics;

    public:
        size_t GetId() const;
        const std::string &GetName() const;

    protected:
        ::Engine::Window *const GetWindow() const;
        ::Engine::TimeModule *const GetTime() const;
        ::Engine::UIModule *const GetUI() const;
        ::Engine::InputModule *const GetInput() const;
        ::Engine::GraphicsModule *const GetGraphics() const;

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

        template<typename Object = GameObject, typename = std::enable_if_t<std::is_base_of_v<GameObject, Object>>>
        Object *CopyGameObject(const std::string &name, Object &&object)
        {
            Object *copyObject = new Object(std::forward<Object>(object));
            static_cast<GameObject *>(copyObject)->name = name;
            objects.insert(std::make_pair(name, copyObject));
            return copyObject;
        }

        template<typename Object = GameObject, typename = std::enable_if_t<std::is_base_of_v<GameObject, Object>>>
        Object *CopyGameObject(Object &&object)
        {
            Object *copyObject = new Object(std::forward<Object>(object));
            objects.insert(std::make_pair(name, copyObject));
            return copyObject;
        }

        template<typename Object = GameObject, typename = std::enable_if_t<std::is_base_of_v<GameObject, Object>>>
        Object *CopyGameObject(const std::string &name, const Object &object)
        {
            Object *copyObject = new Object(object);
            static_cast<GameObject *>(copyObject)->name = name;
            objects.insert(std::make_pair(name, copyObject));
            return copyObject;
        }

        template<typename Object = GameObject, typename = std::enable_if_t<std::is_base_of_v<GameObject, Object>>>
        Object *CopyGameObject(const Object &object)
        {
            Object *copyObject = new Object(object);
            static_cast<GameObject *>(copyObject)->name += "_Copy";
            objects.insert(std::make_pair(name, copyObject));
            return copyObject;
        }

        void UpdateGameObject(const std::string &name);
        void RemoveGameObject(GameObject *object);
        void ClearObjects();
        GameObject *const GetGameObject(const std::string &name);

    public:
        const GameObject *const GetGameObject(const std::string &name) const;
        const std::unordered_map<std::string, GameObject *> &GetGameObjects() const;
        bool ContainsGameObjects(GameObject *object);

    private:
        std::unordered_map<std::string, GameObject *> objects;

    private:
        static size_t idCounter;
    };
}