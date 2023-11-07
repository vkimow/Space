#pragma once

#include "Engine/UI/Menu/MenuUI.h"

namespace Engine::UI
{
    class PostProcessingMenu;

    class PostProcessingMenuUI final: public MenuUI
    {
        friend class PostProcessingMenu;

    private:
        PostProcessingMenuUI(PostProcessingMenu *const menu);
        PostProcessingMenuUI(const PostProcessingMenuUI &rhs) = delete;
        PostProcessingMenuUI(PostProcessingMenuUI &&rhs) noexcept = delete;
        PostProcessingMenuUI &operator=(const PostProcessingMenuUI &rhs) = delete;
        PostProcessingMenuUI &operator=(PostProcessingMenuUI &&rhs) noexcept = delete;
        ~PostProcessingMenuUI() = default;

    protected:
        void UpdateInner() override final;
    };
}