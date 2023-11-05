#include "Engine/UI/Menu/MenuManager.h"
#include <imgui.h>

namespace Engine::UI
{
    MenuManager::MenuManager(EditorManager *editorManager)
        : container()
    {}

    MenuManager::~MenuManager()
    {}

    MenuContainer &MenuManager::GetContainer()
    {
        return container;
    }

    void MenuManager::Update()
    {
        for (auto it = container.begin(); it != container.end(); ++it)
        {
            if (it->element->IsActive())
            {
                it->element->Update();
            }
        }
    }
}

