#include "Space/Menus/SpaceTime/SpaceTimeMenuUI.h"
#include "Space/Menus/SpaceTime/SpaceTimeMenu.h"
#include <imgui.h>

namespace Main::Space
{
    SpaceTimeMenuUI::SpaceTimeMenuUI(SpaceTimeMenu *const menu)
        : MenuUI(menu, 320.0f,80.0f)
    {}

    void SpaceTimeMenuUI::UpdateInner()
    {
        SpaceTimeMenu *menu = GetMenu<SpaceTimeMenu>();
        ImGui::Text("Time Coefficient: %.1f", menu->GetTimeCoef());
        std::vector<float> coefficients{1.0f, 2.0f, 5.0f, 10.0f, 25.0f, 50.f, 100.f};
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