#pragma once

#include "Engine/Tools/Structs/IndividualTypeContainerWithPriority.h"
#include "Engine/UI/Editor/Editor.h"

namespace Engine
{
    class UIModule;
}

namespace Engine::UI
{
    class EditorContainer
    {
        friend class EditorManager;

    private:
        EditorContainer();
        EditorContainer(const EditorContainer &rhs) = delete;
        EditorContainer(EditorContainer &&rhs) = delete;
        EditorContainer &operator=(const EditorContainer &rhs) = delete;
        EditorContainer &operator=(EditorContainer &&rhs) = delete;
        ~EditorContainer();

    public:
        template<typename E, typename = std::enable_if_t<std::is_base_of_v<Editor, E>>>
        E *const Create()
        {
            E *editor = new E();
            std::type_index editorType = std::type_index(typeid(E));
            Editor *editorBase = static_cast<Editor *>(editor);
            editors.Add(editor, editorBase->GetDefaultPriority());
            scriptToEditor.emplace(editorType, std::make_unique<std::type_index>(editorBase->GetScriptType()));
            return editor;
        }

        template<typename E, typename = std::enable_if_t<std::is_base_of_v<Editor, E>>>
        E *const Get()
        {
            return editors.Get<E>();
        }

        template<typename S, typename = std::enable_if_t<std::is_base_of_v<Objects::Script, S>>>
        Editor *const GetByScript()
        {
            std::type_index scriptType = std::type_index(typeid(S));
            return GetByScript(scriptType);
        }

        Editor *const GetByScript(const std::type_index scriptType)
        {
            std::type_index editorType = *(scriptToEditor[scriptType]);
            return editors.Get(editorType);
        }

        template<typename S, typename = std::enable_if_t<std::is_base_of_v<Objects::Script, S>>>
        bool ContainsByScript()
        {
            std::type_index scriptType = std::type_index(typeid(S));
            return ContainsByScript(scriptType);
        }

        bool ContainsByScript(const std::type_index scriptType)
        {
            if (!scriptToEditor.contains(scriptType))
            {
                return false;
            }

            std::type_index editorType = *(scriptToEditor[scriptType]);
            return editors.Contains(editorType);
        }

    public:
        auto begin() { return editors.begin(); }
        auto end() { return editors.end(); }
        auto begin() const { return editors.begin(); }
        auto end() const { return editors.end(); }

    private:
        Tools::Structs::IndividualTypeContainerWithPriority<Editor> editors;
        std::unordered_map<std::type_index, std::unique_ptr<std::type_index>> scriptToEditor;
    };
}