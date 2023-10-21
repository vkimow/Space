#include "Engine/Objects/GameObject.h"
#include <algorithm>

namespace Engine::Objects
{
    GameObject::GameObject()
        : name()
        , tranform()
        , scripts()
        , typeToIndex()
    {}

    GameObject::GameObject(const std::string& name)
        : GameObject(name, Transform())
    {}

    GameObject::GameObject(const std::string& name, const Transform & transform)
        : name(name)
        , tranform(transform)
        , scripts()
        , typeToIndex()
    {}

    GameObject::GameObject(const std::string& name, Transform && transform)
        : name(name)
        , tranform(transform)
        , scripts()
        , typeToIndex()
    {}

    GameObject::GameObject(const GameObject & rhs) noexcept
        : name()
        , tranform(rhs.tranform)
        , scripts(rhs.scripts)
        , typeToIndex(rhs.typeToIndex)
    {
        auto it = scripts.begin();
        auto rhsIt = rhs.scripts.begin();
        for (;rhsIt != rhs.scripts.end(); ++it, ++rhsIt)
        {
            Script *clonedScript = rhsIt->script->Clone();
            clonedScript->SetGameObject(this);
            it->script = clonedScript;
        }
    }

    GameObject::GameObject(GameObject && rhs) noexcept
        : name(std::move(rhs.name))
        , tranform(std::move(rhs.tranform))
        , scripts(std::move(rhs.scripts))
        , typeToIndex(std::move(rhs.typeToIndex))
    {
        for (auto it = scripts.begin(); it != scripts.end(); ++it)
        {
            it->script->SetGameObject(this);
        }

        rhs.scripts.clear();
        rhs.typeToIndex.clear();
    }

    GameObject &GameObject::operator=(const GameObject & rhs)
    {
        tranform = rhs.tranform;
        DeleteScripts();
        scripts = rhs.scripts;
        typeToIndex = rhs.typeToIndex;

        auto it = scripts.begin();
        auto rhsIt = rhs.scripts.begin();
        for (; it != rhs.scripts.end(); ++it, ++rhsIt)
        {
            Script *clonedScript = rhsIt->script->Clone();
            clonedScript->SetGameObject(this);
            it->script = clonedScript;
        }
        return *this;
    }

    GameObject &GameObject::operator=(GameObject &&rhs) noexcept
    {
        name = std::move(rhs.name);
        tranform = std::move(rhs.tranform);
        DeleteScripts();
        scripts = std::move(rhs.scripts);
        typeToIndex = std::move(rhs.typeToIndex);
        for (auto it = scripts.begin(); it != scripts.end(); ++it)
        {
            it->script->SetGameObject(this);
        }

        rhs.scripts.clear();
        rhs.typeToIndex.clear();
        return *this;
    }

    GameObject::~GameObject()
    {
        ClearScripts();
    }

    const std::string &GameObject::GetName() const
    {
        return name;
    }

    Transform &GameObject::GetTransform()
    {
        return tranform;
    }

    Transform *GameObject::GetTransformPtr()
    {
        return &tranform;
    }

    void GameObject::UpdateTypeToIndexByScripts(size_t start)
    {
        if (start >= scripts.size())
        {
            LOG_ERROR("Can't update order after the end of vector");
        }

        for (auto it = scripts.begin() + start; it != scripts.end(); ++it)
        {
            typeToIndex[it->type] = it - scripts.begin();
        }
    }

    void GameObject::SortScriptsAfterPriorityChangeOfOneElement(size_t start)
    {
        if (start >= scripts.size())
        {
            LOG_ERROR("Can't update order after the end of vector");
        }

        auto changedElementIt = scripts.begin() + start;
        auto nextElementIt = changedElementIt + 1;
        const size_t changedElementPriority = changedElementIt->priority;
        while (nextElementIt != scripts.end() || changedElementPriority > nextElementIt->priority)
        {
            std::iter_swap(changedElementIt, nextElementIt);
            ++changedElementIt;
            ++nextElementIt;
        }
    }

    void GameObject::ClearScripts()
    {
        DeleteScripts();
        scripts.clear();
        typeToIndex.clear();
    }

    void GameObject::DeleteScripts()
    {
        for (auto it = scripts.begin(); it != scripts.end(); ++it)
        {
            delete it->script;
        }
    }

    void GameObject::Update()
    {
        for (auto it = scripts.begin(); it != scripts.end(); ++it)
        {
            it->script->Update();
        }
    }
}
