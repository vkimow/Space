#include "Engine/Essentials/Menus/Time/TimeMenu.h"
#include "Engine/Essentials/Menus/Time/TimeMenuUI.h"

namespace Engine::UI
{
    TimeMenu::TimeMenu()
        : Menu("Time", new TimeMenuUI(this))
    {}

    TimeMenu::~TimeMenu()
    {}

    void TimeMenu::Update()
    {}

    size_t TimeMenu::GetDefaultPriority() const
    {
        return priority;
    }
}