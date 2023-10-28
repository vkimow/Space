#pragma once

#include "Engine/Tools/Structs/IndividualTypeContainerWithPriority.h"
#include "Engine/UI/Editor/Editor.h"
#include "Engine/UI/Editor/EditorContainer.h"

namespace Engine
{
    class UIModule;
}

namespace Engine::UI
{
    class EditorManager
    {
        friend class UIModule;

    private:
        EditorManager();
        EditorManager(const EditorManager &rhs) = delete;
        EditorManager(EditorManager &&rhs) = delete;
        EditorManager &operator=(const EditorManager &rhs) = delete;
        EditorManager &operator=(EditorManager &&rhs) = delete;
        ~EditorManager();

    public:
        void SetTarget(Objects::GameObject *const object);
        void UnsetTarget();
        void SetActive(bool value);

    private:
        void Update();

    public:
        bool IsActive() const;
        EditorContainer &GetContainer();

    private:
        bool isActive;
        Objects::GameObject *target;
        EditorContainer container;
    };
}