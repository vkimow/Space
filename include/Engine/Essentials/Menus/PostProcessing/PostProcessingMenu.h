#pragma once
#include "Engine/UI/Menu/Menu.h"
#include "Engine/UI/Menu/MenuContainer.h"
#include "Engine/UI/Editor/EditorManager.h"
#include "Engine/UI/Buffer.h"
#include "Engine/Graphics/PostProcessing/PostProcessingManager.h"

namespace Engine::UI
{
    class PostProcessingMenu final: public Menu
    {
        friend class MenuContainer;
        friend class PostProcessingMenuUI;

    private:
        PostProcessingMenu(Graphics::PostProcessingManager *postProcessing);
        PostProcessingMenu(const PostProcessingMenu &rhs) = delete;
        PostProcessingMenu(PostProcessingMenu &&rhs) noexcept = delete;
        PostProcessingMenu &operator=(const PostProcessingMenu &rhs) = delete;
        PostProcessingMenu &operator=(PostProcessingMenu &&rhs) noexcept = delete;
        ~PostProcessingMenu();

    public:
        void Update() override final;
        size_t GetDefaultPriority() const override final;

    private:
        void UpdateFromTarget();
        void UpdateFromUI();

    private:
        Buffer<float> gamma;
        Buffer<float> exposure;
        Buffer<float> bloomThreshold;

    private:
        Graphics::PostProcessingManager *const postProcessing;

    private:
        static const size_t priority;
    };
}