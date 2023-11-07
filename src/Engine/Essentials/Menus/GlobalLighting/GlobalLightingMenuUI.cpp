#include "Engine/Essentials/Menus/GlobalLighting/GlobalLightingMenu.h"
#include "Engine/Essentials/Menus/GlobalLighting/GlobalLightingMenuUI.h"
#include <imgui.h>
#include "Engine/Tools/Other/ImGui.h"

namespace Engine::UI
{
    GlobalLightingMenuUI::GlobalLightingMenuUI(GlobalLightingMenu *const menu)
        : MenuUI(menu, 400.0f, 300.0f, ImGuiWindowFlags_::ImGuiWindowFlags_None)
    {}

    void GlobalLightingMenuUI::UpdateInner()
    {
        GlobalLightingMenu *const menu = GetMenu<GlobalLightingMenu>();

        ImGui::Checkbox("##ActiveAmbient", menu->GetIsAmbientEnabled().GetBufferPtr());
        ImGui::SameLine();
        if (ImGui::CollapsingHeader("Ambient Light", ImGuiTreeNodeFlags_DefaultOpen))
        {
            if (menu->GetIsAmbientEnabled())
            {
                ImGui::LightValue("Light", menu->GetAmbientLight().GetBuffer());
            }
        }
        //ImGui::Checkbox("##ActiveDirectional", menu->GetIsDirectionalEnabled().GetBufferPtr());
        //ImGui::SameLine();
        //if (ImGui::CollapsingHeader("Directional Light", ImGuiTreeNodeFlags_DefaultOpen))
        //{
        //    if (menu->GetIsDirectionalEnabled())
        //    {
        //        ImGui::InputVector3("Direction##Directional", menu->GetDirectionalDirection().GetBuffer());
        //        ImGui::LightValue("Diffuse", menu->GetDirectionalDiffuse().GetBuffer());
        //        ImGui::LightValue("Specular", menu->GetDirectionalSpecular().GetBuffer());
        //    }
        //}
    }
}