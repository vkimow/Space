#pragma once

#include <string>
#include "Engine/Objects/GameObject.h"
#include "Engine/Tools/Structs/StructsHeader.h"

namespace Engine
{
    class Window;
    class GraphicsModule;
    class TimeModule;
    class InputModule;
    class UIModule;
}

namespace Engine::Managers
{
    class GameObjectManager;
    class GameObjectEditorManager;
}

namespace Engine::Objects
{
    class Scene
    {
        using GameObjectsContainer = Tools::Structs::MapWithPriority<std::string, GameObject>;

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

    public:
        template<typename... Args>
        GameObject *CreateGameObject(const std::string &name, size_t priority, Args&&... args)
        {
            GameObject *object = new GameObject(name, std::forward<Args>(args)...);
            objects.Add(name, priority, object);
            return object;
        }

        template<typename... Args>
        GameObject *CreateGameObject(const std::string &name, Args&&... args)
        {
            return CreateGameObject(name, objects.Size(), std::forward<Args>(args)...);
        }

        GameObject *CreateGameObject(const std::string &name, size_t priority);
        GameObject *CreateGameObject(const std::string &name);

        GameObject *CopyGameObject(const std::string &name, size_t priority, GameObject &&object);
        GameObject *CopyGameObject(const std::string &name, GameObject &&object);
        GameObject *CopyGameObject(size_t priority, GameObject &&object);
        GameObject *CopyGameObject(GameObject &&object);
        GameObject *CopyGameObject(const std::string &name, size_t priority, const GameObject &object);
        GameObject *CopyGameObject(const std::string &name, const GameObject &object);
        GameObject *CopyGameObject(size_t priority, const GameObject &object);
        GameObject *CopyGameObject(const GameObject &object);

        GameObject *const GetGameObject(const std::string &name);
        const GameObject *const GetGameObject(const std::string &name) const;

        GameObjectsContainer &GetGameObjects();
        const GameObjectsContainer &GetGameObjects() const;

        bool ContainsGameObject(GameObject *object) const;
        bool ContainsGameObject(const std::string &name) const;

        void RemoveGameObject(GameObject *object);
        void RemoveGameObject(const std::string &name);

        void ClearObjects();

    private:
        GameObjectsContainer objects;

    private:
        static size_t idCounter;
    };
}