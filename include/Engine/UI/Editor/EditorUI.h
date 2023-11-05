#pragma once

#include <type_traits>
#include <string>

namespace Engine::UI
{
    class Editor;

    class EditorUI
    {
        friend class Editor;

    protected:
        EditorUI(Editor *const editor, bool shouldNotUseCollapsingHeader = false, bool shouldNotBeDisabled = false);
        EditorUI(const EditorUI &rhs) = delete;
        EditorUI(EditorUI &&rhs) noexcept = delete;
        EditorUI &operator=(const EditorUI &rhs) = delete;
        EditorUI &operator=(EditorUI &&rhs) noexcept = delete;
        virtual ~EditorUI();

    private:
        void Update();

    protected:
        virtual void UpdateInner() = 0;

    protected:
        template<typename E = Editor, typename = std::enable_if_t<std::is_base_of_v<Editor, E>>>
        E *const GetEditor() const { return static_cast<E *const>(editor); };
        std::string GetVariableName(const std::string &name) const;
        const std::string& GetEditorName() const;

    private:
        Editor *const editor;
        bool shouldNotUseCollapsingHeader;
        bool shouldNotBeDisabled;
    };
}