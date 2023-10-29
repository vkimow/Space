#include "Space/Menus/SpaceTime/SpaceTimeMenu.h"
#include "Space/Menus/SpaceTime/SpaceTimeMenuUI.h"

namespace Main::Space
{
    SpaceTimeMenu::SpaceTimeMenu(SpaceTime *time)
        : Menu("SpaceTime", new SpaceTimeMenuUI(this))
        , time(time)
    {}

    SpaceTimeMenu::~SpaceTimeMenu()
    {}

    void SpaceTimeMenu::Update()
    {
        UpdateUI();
    }

    size_t SpaceTimeMenu::GetDefaultPriority() const
    {
        return priority;
    }

    float SpaceTimeMenu::GetTimeCoef() const
    {
        return time->GetTimeCoef();
    }

    void SpaceTimeMenu::SetTimeCoef(float value)
    {
        time->SetTimeCoef(value);
    }
}