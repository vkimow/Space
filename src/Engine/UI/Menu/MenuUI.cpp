#include "Engine/UI/Menu/MenuUI.h"
#include "Engine/UI/Menu/Menu.h"
#include <imgui.h>

namespace Engine::UI
{
    MenuUI::MenuUI(Menu *const menu, float width, float height, ImGuiWindowFlags_ flags)
        : menu(menu)
        , size(width, height)
        , flags(flags)
    {}

    MenuUI::~MenuUI()
    {}

    void MenuUI::Update()
    {
        ImGui::SetNextWindowSize(size, ImGuiCond_::ImGuiCond_Appearing);
        ImGui::Begin(menu->GetName().c_str(), nullptr, flags);
        UpdateInner();
        ImGui::End();
    }
}