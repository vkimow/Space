#include "Engine/Essentials/Editors/Transform/TransformEditor.h"
#include "Engine/Essentials/Editors/Transform/TransformEditorUI.h"


namespace Engine::UI
{
    TransformEditor::TransformEditor()
        : Editor("Transform", new TransformEditorUI(this), false)
        , position(0.0f)
        , rotation(0.0f)
        , scale(0.0f)
    {}

    TransformEditor::~TransformEditor()
    {}

    size_t TransformEditor::GetDefaultPriority() const
    {
        return priority;
    }

    std::type_index TransformEditor::GetScriptType() const
    {
        return std::type_index(typeid(Objects::Transform));
    }

    void TransformEditor::UpdateFromTarget()
    {
        auto &transform = GetTarget()->GetTransform();
        position = transform.GetPosition();
        rotation = transform.GetRotationInDegrees();
        scale = transform.GetScale();
    }

    void TransformEditor::UpdateFromUI()
    {
        if (position.IsValueDiffersFromBuffer())
        {
            position.SetValueToBuffer();
            GetTarget()->GetTransform().SetPosition(position);
        }

        if (rotation.IsValueDiffersFromBuffer())
        {
            rotation.SetValueToBuffer();
            GetTarget()->GetTransform().SetRotationInDegrees(rotation);
        }

        if (scale.IsValueDiffersFromBuffer())
        {
            scale.SetValueToBuffer();
            GetTarget()->GetTransform().SetScale(scale);
        }
    }

    Buffer<glm::vec3> &TransformEditor::GetPosition()
    {
        return position;
    }

    Buffer<glm::vec3> &TransformEditor::GetRotation()
    {
        return rotation;
    }

    Buffer<glm::vec3> &TransformEditor::GetScale()
    {
        return scale;
    }
}