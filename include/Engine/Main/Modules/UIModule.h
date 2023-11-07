#pragma once

namespace Engine::UI
{
    class MenuManager;
    class EditorManager;
}

struct GLFWwindow;
struct ImGuiIO;
namespace Engine
{
    class InputModule;

    class UIModule
    {
        friend class Engine;
        friend class InputModule;

    private:
        UIModule(GLFWwindow *const window);

        UIModule() = delete;
        UIModule(const UIModule &rhs) = delete;
        UIModule(UIModule &&rhs) = delete;
        UIModule &operator=(const UIModule &rhs) = delete;
        UIModule &operator=(UIModule &&rhs) = delete;

        ~UIModule();

    private:
        void NewFrame();
        void Update();
        void Render();

    private:
        bool WantCaptureInput() const;
        bool WantCaptureKeyboard() const;
        bool WantCaptureMouse() const;

    public:
        UI::MenuManager *const GetMenuManager();
        UI::EditorManager *const GetEditorManager();

    private:
        ImGuiIO *inputOutput;
        UI::EditorManager *const editorManager;
        UI::MenuManager *const menuManager;
    };
}