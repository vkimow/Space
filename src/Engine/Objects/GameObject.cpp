#include "Engine/Objects/GameObject.h"
#include <algorithm>

namespace Engine::Objects
{
    GameObject::GameObject()
        : isActive(false)
        , isInvisible(false)
        , name()
        , tranform()
        , scripts()
    {}

    GameObject::GameObject(const std::string &name)
        : GameObject(name, Transform())
    {}

    GameObject::GameObject(const std::string &name, const Transform &transform)
        : isActive(true)
        , isInvisible(false)
        , name(name)
        , tranform(transform)
        , scripts()
    {}

    GameObject::GameObject(const std::string &name, Transform &&transform)
        : isActive(true)
        , isInvisible(false)
        , name(name)
        , tranform(transform)
        , scripts()
    {}

    GameObject::GameObject(const GameObject &rhs) noexcept
        : isActive(rhs.isActive)
        , isInvisible(rhs.isInvisible)
        , name(rhs.name + "_copy")
        , tranform(rhs.tranform)
        , scripts(rhs.scripts)
    {
        for (auto it = scripts.begin(); it != scripts.end(); ++it)
        {
            it->element->SetGameObject(this);
            it->element->OnEnabled();
        }
    }

    GameObject::GameObject(GameObject &&rhs) noexcept
        : isActive(rhs.isActive)
        , isInvisible(rhs.isInvisible)
        , name(std::move(rhs.name))
        , tranform(std::move(rhs.tranform))
        , scripts(std::move(rhs.scripts))
    {
        for (auto it = scripts.begin(); it != scripts.end(); ++it)
        {
            it->element->SetGameObject(this);
            it->element->OnEnabled();
        }
    }

    GameObject &GameObject::operator=(const GameObject &rhs)
    {
        isActive = rhs.isActive;
        isInvisible = rhs.isInvisible;
        tranform = rhs.tranform;
        scripts = rhs.scripts;
        for (auto it = scripts.begin(); it != scripts.end(); ++it)
        {
            it->element->SetGameObject(this);
            it->element->OnEnabled();
        }
        return *this;
    }

    GameObject &GameObject::operator=(GameObject &&rhs) noexcept
    {
        isActive = rhs.isActive;
        isInvisible = rhs.isInvisible;
        name = std::move(rhs.name);
        tranform = std::move(rhs.tranform);
        scripts = std::move(rhs.scripts);
        for (auto it = scripts.begin(); it != scripts.end(); ++it)
        {
            it->element->SetGameObject(this);
            it->element->OnEnabled();
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

    bool GameObject::IsInvisible() const
    {
        return isInvisible;
    }

    void GameObject::SetActive(bool value)
    {
        isActive = value;

        if (isActive)
        {
            EnableScripts();
        }
        else
        {
            DisableScripts();
        }
    }

    void GameObject::SetInvisible(bool value)
    {
        isInvisible = value;
    }

    void GameObject::EnableScripts()
    {
        for (auto it = scripts.begin(); it != scripts.end(); ++it)
        {
            it->element->OnEnabled();
        }
    }

    void GameObject::DisableScripts()
    {
        for (auto it = scripts.begin(); it != scripts.end(); ++it)
        {
            it->element->OnDisabled();
        }
    }

    Script *const GameObject::GetScript(const std::type_index &type)
    {
        return scripts.Get(type);
    }

    void GameObject::Update()
    {
        if (!IsActive())
        {
            return;
        }

        for (auto it = scripts.begin(); it != scripts.end(); ++it)
        {
            if (!it->element->IsActive())
            {
                continue;
            }

            it->element->Update();
        }
    }

    void GameObject::UpdateEditor()
    {
        if (!IsActive())
        {
            return;
        }

        for (auto it = scripts.begin(); it != scripts.end(); ++it)
        {
            if (!it->element->IsActive())
            {
                continue;
            }

            it->element->UpdateEditor();
        }
    }

    void GameObject::SelectEditor()
    {
        if (!IsActive())
        {
            return;
        }

        for (auto it = scripts.begin(); it != scripts.end(); ++it)
        {
            if (!it->element->IsActive())
            {
                continue;
            }

            it->element->SelectEditor();
        }
    }

    void GameObject::DeselectEditor()
    {
        if (!IsActive())
        {
            return;
        }

        for (auto it = scripts.begin(); it != scripts.end(); ++it)
        {
            if (!it->element->IsActive())
            {
                continue;
            }

            it->element->DeselectEditor();
        }
    }
}
