#include "Engine/Essentials/Menus/PostProcessing/PostProcessingMenu.h"
#include "Engine/Essentials/Menus/PostProcessing/PostProcessingMenuUI.h"
#include <imgui.h>
#include "Engine/Tools/Other/ImGui.h"

namespace Engine::UI
{
    PostProcessingMenuUI::PostProcessingMenuUI(PostProcessingMenu *const menu)
        : MenuUI(menu, 400.0f, 300.0f, ImGuiWindowFlags_::ImGuiWindowFlags_None)
    {}

    void PostProcessingMenuUI::UpdateInner()
    {
        PostProcessingMenu *const menu = GetMenu<PostProcessingMenu>();
        ImGui::DragFloat("Gamma", menu->gamma.GetBufferPtr(), 0.01f, 0.0f, 100.0f);
        ImGui::DragFloat("Exposure", menu->exposure.GetBufferPtr(), 0.01f, 0.0f, 100.0f);
        ImGui::DragFloat("Bloom Threshold", menu->bloomThreshold.GetBufferPtr(), 0.01f, 0.0f, 100.0f);
    }
}