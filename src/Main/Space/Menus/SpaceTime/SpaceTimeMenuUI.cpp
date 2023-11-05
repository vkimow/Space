#include "Space/Menus/SpaceTime/SpaceTimeMenuUI.h"
#include "Space/Menus/SpaceTime/SpaceTimeMenu.h"
#include <imgui.h>

namespace Main::Space
{
    SpaceTimeMenuUI::SpaceTimeMenuUI(SpaceTimeMenu *const menu)
        : MenuUI(menu, 220.0f,80.0f)
    {}

    void SpaceTimeMenuUI::UpdateInner()
    {
        SpaceTimeMenu *menu = GetMenu<SpaceTimeMenu>();
        ImGui::Text("Time Coefficient: %.1f", menu->GetTimeCoef());
        std::vector<float> coefficients{0.1f, 0.5f, 1.0f, 2.0f, 5.0f};
        for (float coefficient : coefficients)
        {
            std::ostringstream floatSS;
            floatSS << std::fixed;
            floatSS << std::setprecision(1);
            floatSS << coefficient;
            if (ImGui::Button(floatSS.str().c_str()))
            {
                menu->SetTimeCoef(coefficient);
            }
            ImGui::SameLine();
        }
    }
}