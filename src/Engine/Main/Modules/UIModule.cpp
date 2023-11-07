#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Engine/Main/Modules/UIModule.h"
#include "Engine/UI/UIHeader.h"
#include "Engine/Tools/Other/ImGui.h"

namespace Engine
{
    UIModule::UIModule(GLFWwindow *const window)
        : inputOutput(nullptr)
        , editorManager(new UI::EditorManager())
        , menuManager(new UI::MenuManager(editorManager))
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        inputOutput = &ImGui::GetIO();  (void)inputOutput;
        inputOutput->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        inputOutput->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 130");

        ImGui::InitializeStyle();
    }

    UIModule::~UIModule()   
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        delete editorManager;
    }

    void UIModule::NewFrame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void UIModule::Update()
    {
        menuManager->Update();
        editorManager->Update();
        ImGui::Render();
    }

    void UIModule::Render()
    {
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    bool UIModule::WantCaptureInput() const
    {
        return WantCaptureKeyboard() || WantCaptureMouse();
    }

    bool UIModule::WantCaptureKeyboard() const
    {
        return inputOutput->WantCaptureKeyboard;
    }

    bool UIModule::WantCaptureMouse() const
    {
        return inputOutput->WantCaptureMouse;
    }

    UI::EditorManager *const UIModule::GetEditorManager()
    {
        return editorManager;
    }

    UI::MenuManager *const UIModule::GetMenuManager()
    {
        return menuManager;
    }
}