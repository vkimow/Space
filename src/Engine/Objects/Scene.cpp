#pragma once

#include <GL/glew.h>
#include <string>
#include "Engine/Objects/Scene.h"
#include "Engine/Essentials/Scripts/ScriptsHeader.h"

namespace Engine::Objects
{
    size_t Scene::idCounter = 0;

    Scene::Scene(const std::string &name, ::Engine::Window *const window, ::Engine::TimeModule *const time, ::Engine::UIModule *const ui, ::Engine::InputModule *const input, ::Engine::GraphicsModule *const graphics)
        : name(name)
        , window(window)
        , time(time)
        , ui(ui)
        , input(input)
        , graphics(graphics)
        , id(idCounter++)
    {}

    Scene::~Scene()
    {
        ClearObjects();
    }

    size_t Scene::GetId() const
    {
        return id;
    }

    const std::string &Scene::GetName() const
    {
        return name;
    }

    Engine::Window *const Scene::GetWindow() const
    {
        return window;
    }

    Engine::TimeModule *const Scene::GetTime() const
    {
        return time;
    }

    ::Engine::UIModule *const Scene::GetUI() const
    {
        return ui;
    }

    Engine::InputModule *const Scene::GetInput() const
    {
        return input;
    }

    Engine::GraphicsModule *const Scene::GetGraphics() const
    {
        return graphics;
    }

    GameObject *Scene::CreateGameObject(const std::string &name, size_t priority)
    {
        GameObject *object = new GameObject(name);
        objects.Add(name, priority, object);
        return object;
    }

    GameObject *Scene::CreateGameObject(const std::string &name)
    {
        return CreateGameObject(name, objects.Size());
    }

    GameObject *Scene::CopyGameObject(const std::string &name, size_t priority, GameObject &&object)
    {
        GameObject *copyObject = new GameObject(std::forward<GameObject>(object));
        copyObject->name = name;
        objects.Add(name, priority, copyObject);
        return copyObject;
    }

    GameObject *Scene::CopyGameObject(const std::string &name, GameObject &&object)
    {
        return CopyGameObject(name, objects.Size(), std::forward<GameObject>(object));
    }

    GameObject *Scene::CopyGameObject(size_t priority, GameObject &&object)
    {
        GameObject *copyObject = new GameObject(std::forward<GameObject>(object));
        objects.Add(copyObject->GetName(), priority, copyObject);
        return copyObject;
    }

    GameObject *Scene::CopyGameObject(GameObject &&object)
    {
        return CopyGameObject(objects.Size(), std::forward<GameObject>(object));
    }

    GameObject *Scene::CopyGameObject(const std::string &name, size_t priority, const GameObject &object)
    {
        GameObject *copyObject = new GameObject(object);
        copyObject->name = name;
        objects.Add(name, priority, copyObject);
        return copyObject;
    }

    GameObject *Scene::CopyGameObject(const std::string &name, const GameObject &object)
    {
        return CopyGameObject(name, objects.Size(), object);
    }

    GameObject *Scene::CopyGameObject(size_t priority, const GameObject &object)
    {
        GameObject *copyObject = new GameObject(object);
        copyObject->name += "_Copy";
        objects.Add(copyObject->GetName(), priority, copyObject);
        return copyObject;
    }

    GameObject *Scene::CopyGameObject(const GameObject &object)
    {
        return CopyGameObject(objects.Size(), object);
    }

    GameObject *const Scene::GetGameObject(const std::string &name)
    {
        return objects.Get(name);
    }

    const GameObject *const Scene::GetGameObject(const std::string &name) const
    {
        return objects.Get(name);
    }

    Scene::GameObjectsContainer &Scene::GetGameObjects()
    {
        return objects;
    }

    const Scene::GameObjectsContainer &Scene::GetGameObjects() const
    {
        return objects;
    }

    bool Scene::ContainsGameObject(GameObject *object) const
    {
        return objects.Contains(object->name);
    }

    bool Scene::ContainsGameObject(const std::string &name) const
    {
        return objects.Contains(name);
    }

    void Scene::RemoveGameObject(GameObject *object)
    {
        objects.Remove(object->name);
    }

    void Scene::RemoveGameObject(const std::string &name)
    {
        objects.Remove(name);
    }

    void Scene::ClearObjects()
    {
        objects.Clear();
    }
}