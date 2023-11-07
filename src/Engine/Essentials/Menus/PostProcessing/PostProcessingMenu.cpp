#include "Engine/Essentials/Menus/PostProcessing/PostProcessingMenu.h"
#include "Engine/Essentials/Menus/PostProcessing/PostProcessingMenuUI.h"

namespace Engine::UI
{
    PostProcessingMenu::PostProcessingMenu(Graphics::PostProcessingManager *postProcessing)
        : Menu("PostProcessing", new PostProcessingMenuUI(this))
        , postProcessing(postProcessing)
    {}

    PostProcessingMenu::~PostProcessingMenu()
    {}

    void PostProcessingMenu::Update()
    {
        UpdateFromTarget();
        UpdateUI();
        UpdateFromUI();
    }

    size_t PostProcessingMenu::GetDefaultPriority() const
    {
        return priority;
    }

    void PostProcessingMenu::UpdateFromTarget()
    {
        gamma = postProcessing->GetSettings().GetGamma();
        exposure = postProcessing->GetSettings().GetExposure();
        bloomThreshold = postProcessing->GetSettings().GetBloomThreshold();
    }

    void PostProcessingMenu::UpdateFromUI()
    {
        if (gamma.IsValueDiffersFromBuffer())
        {
            gamma.SetValueToBuffer();
            postProcessing->GetSettings().SetGamma(gamma);
        }

        if (exposure.IsValueDiffersFromBuffer())
        {
            exposure.SetValueToBuffer();
            postProcessing->GetSettings().SetExposure(exposure);
        }

        if (bloomThreshold.IsValueDiffersFromBuffer())
        {
            bloomThreshold.SetValueToBuffer();
            postProcessing->GetSettings().SetBloomThreshold(bloomThreshold);
        }
    }
}