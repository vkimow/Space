#include "Engine/Objects/GameObject.h"
#include <algorithm>

namespace Engine::Objects
{
    GameObject::GameObject()
        : name()
        , tranform()
        , scripts()
    {}

    GameObject::GameObject(const std::string &name)
        : GameObject(name, Transform())
    {}

    GameObject::GameObject(const std::string &name, const Transform &transform)
        : name(name)
        , tranform(transform)
        , scripts()
    {}

    GameObject::GameObject(const std::string &name, Transform &&transform)
        : name(name)
        , tranform(transform)
        , scripts()
    {}

    GameObject::GameObject(const GameObject &rhs) noexcept
        : name()
        , tranform(rhs.tranform)
        , scripts(rhs.scripts)
    {
        for (auto it = scripts.begin(); it != scripts.end(); ++it)
        {
            it->element->SetGameObject(this);
        }
    }

    GameObject::GameObject(GameObject &&rhs) noexcept
        : name(std::move(rhs.name))
        , tranform(std::move(rhs.tranform))
        , scripts(std::move(rhs.scripts))
    {
        for (auto it = scripts.begin(); it != scripts.end(); ++it)
        {
            it->element->SetGameObject(this);
        }
    }

    GameObject &GameObject::operator=(const GameObject &rhs)
    {
        tranform = rhs.tranform;
        scripts = rhs.scripts;
        for (auto it = scripts.begin(); it != scripts.end(); ++it)
        {
            it->element->SetGameObject(this);
        }
        return *this;
    }

    GameObject &GameObject::operator=(GameObject &&rhs) noexcept
    {
        name = std::move(rhs.name);
        tranform = std::move(rhs.tranform);
        scripts = std::move(rhs.scripts);
        for (auto it = scripts.begin(); it != scripts.end(); ++it)
        {
            it->element->SetGameObject(this);
        }
        return *this;
    }

    GameObject::~GameObject()
    {
        scripts.Clear();
    }

    const std::string &GameObject::GetName() const
    {
        return name;
    }

    Transform &GameObject::GetTransform()
    {
        return tranform;
    }

    Transform * const GameObject::GetTransformPtr()
    {
        return &tranform;
    }

    const Transform &GameObject::GetTransform() const
    {
        return tranform;
    }

    const Transform *const GameObject::GetTransformPtr() const
    {
        return &tranform;
    }

    const GameObject::ScriptsContainer &GameObject::GetScripts() const
    {
        return scripts;
    }

    bool GameObject::IsActive() const
    {
        return isActive;
    }

    void GameObject::SetActive(bool value)
    {
        isActive = value;
    }

    void GameObject::Update()
    {
        if (!IsActive())
        {
            return;
        }

        for (auto it = scripts.begin(); it != scripts.end(); ++it)
        {
            it->element->Update();
        }
    }
}
