#include "Engine/UI/Menu/MenuUI.h"
#include "Engine/UI/Menu/Menu.h"
#include <imgui.h>

namespace Engine::UI
{
    MenuUI::MenuUI(Menu *const menu)
        : menu(menu)
    {}

    MenuUI::~MenuUI()
    {}

    void MenuUI::Update()
    {
        ImGui::Begin(menu->GetName().c_str(), &(menu->isActive));
        UpdateInner();
        ImGui::End();
    }
}