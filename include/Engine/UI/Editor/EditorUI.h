#pragma once

#include <type_traits>

namespace Engine::UI
{
    class Editor;

    class EditorUI
    {
        friend class Editor;

    protected:
        EditorUI(Editor* const editor);
        EditorUI(const EditorUI &rhs) = delete;
        EditorUI(EditorUI &&rhs) noexcept = delete;
        EditorUI &operator=(const EditorUI &rhs) = delete;
        EditorUI &operator=(EditorUI &&rhs) noexcept = delete;
        virtual ~EditorUI();

    protected:
        virtual void UpdateInner() = 0;

    private:
        void Update();

    protected:
        template<typename E, typename = std::enable_if_t<std::is_base_of_v<Editor, E>>>
        E *const GetEditor() { return static_cast<E *const>(editor); }

    private:
        Editor *const editor;
    };
}