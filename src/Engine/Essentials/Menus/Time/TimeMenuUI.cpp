#include "Engine/Essentials/Menus/Time/TimeMenuUI.h"
#include "Engine/Essentials/Menus/Time/TimeMenu.h"
#include <imgui.h>

namespace Engine::UI
{
    TimeMenuUI::TimeMenuUI(TimeMenu *const menu)
        : MenuUI(menu)
    {}

    void TimeMenuUI::UpdateInner()
    {}
}