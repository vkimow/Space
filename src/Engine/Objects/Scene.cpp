#pragma once

#include <string>
#include "Engine/Objects/Scene.h"

namespace Engine::Objects
{
    size_t Scene::idCounter = 0;

    Scene::Scene(const std::string &name, Engine::Window *const window, Engine::TimeModule *const time, Engine::InputModule *const input, Engine::GraphicsModule *const graphics)
        : name(name)
        , window(window)
        , time(time)
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

    Engine::InputModule *const Scene::GetInput() const
    {
        return input;
    }

    Engine::GraphicsModule *const Scene::GetGraphics() const
    {
        return graphics;
    }


    void Scene::UpdateGameObject(const std::string &name)
    {
        objects[name]->Update();
    }

    GameObject *Scene::GetGameObject(const std::string &name)
    {
        return objects[name];
    }

    bool Scene::ContainsGameObjects(GameObject *object)
    {
        return objects.contains(object->name);
    }

    void Scene::RemoveGameObject(GameObject *object)
    {
        objects.erase(object->name);
    }

    void Scene::ClearObjects()
    {
        for (auto it = objects.begin(); it != objects.end(); ++it)
        {
            delete it->second;
        }
        objects.clear();
    }
}