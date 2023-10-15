#include "Engine/Objects/GameObject.h"

namespace Engine::Objects
{
    GameObject::GameObject()
        : name()
        , tranform()
        , scripts()
    {}

    GameObject::GameObject(const std::string& name)
        : GameObject(name, Transform())
    {}

    GameObject::GameObject(const std::string& name, const Transform & transform)
        : name(name)
        , tranform(transform)
        , scripts()
    {}

    GameObject::GameObject(const std::string& name, Transform && transform)
        : name(name)
        , tranform(transform)
        , scripts()
    {}

    GameObject::GameObject(const GameObject & rhs) noexcept
        : name(rhs.name)
        , tranform(rhs.tranform)
        , scripts(rhs.scripts)
    {
        for (auto it = rhs.scripts.begin(); it != rhs.scripts.end(); ++it)
        {
            std::type_index type = it->first;
            Script *script = it->second->Clone();
            if (script)
            {
                scripts[std::move(type)] = script;
            }
        }
    }

    GameObject::GameObject(GameObject && rhs) noexcept
        : name(std::move(rhs.name))
        , tranform(std::move(rhs.tranform))
        , scripts(std::move(rhs.scripts))
    {}

    GameObject &GameObject::operator=(const GameObject & rhs)
    {
        name = rhs.name;
        tranform = rhs.tranform;
        DeleteScripts();

        scripts = rhs.scripts;
        for (auto it = rhs.scripts.begin(); it != rhs.scripts.end(); ++it)
        {
            std::type_index type = it->first;
            Script *script = it->second->Clone();
            if (script)
            {
                scripts[std::move(type)] = script;
            }
        }
        return *this;
    }

    GameObject &GameObject::operator=(GameObject &&rhs) noexcept
    {
        name = std::move(rhs.name);
        tranform = std::move(rhs.tranform);
        DeleteScripts();
        scripts = std::move(rhs.scripts);
        return *this;
    }

    std::string &GameObject::GetName()
    {
        return name;
    }

    Transform &GameObject::GetTransform()
    {
        return tranform;
    }

    void GameObject::ClearScripts()
    {
        DeleteScripts();
        scripts.clear();
    }

    void GameObject::DeleteScripts()
    {
        for (auto it = scripts.begin(); it != scripts.end(); ++it)
        {
            delete it->second;
        }
    }

    GameObject::~GameObject()
    {}
    void GameObject::Update()
    {}
}
