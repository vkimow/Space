#include "Engine/Essentials/Editors/GameObject/GameObjectEditor.h"
#include "Engine/Essentials/Editors/GameObject/GameObjectEditorUI.h"


namespace Engine::UI
{
    GameObjectEditor::GameObjectEditor()
        : Editor("GameObject", new GameObjectEditorUI(this))
        , bufferPosition(0.0f)
        , bufferRotation(0.0f)
        , bufferScale(0.0f)
        , isActive(false)
        , position()
        , rotation()
        , scale()
    {}

    GameObjectEditor::~GameObjectEditor()
    {}

    size_t GameObjectEditor::GetDefaultPriority() const
    {
        return priority;
    }

    std::type_index GameObjectEditor::GetScriptType() const
    {
        return std::type_index(typeid(Objects::GameObject));
    }

    void GameObjectEditor::UpdateFromTarget()
    {
        isActive = GetTarget()->IsActive();

        auto newPosition = GetTarget()->GetTransform().GetPosition();
        if (bufferPosition != newPosition)
        {
            bufferPosition = newPosition;
            position[0] = bufferPosition.x;
            position[1] = bufferPosition.y;
            position[2] = bufferPosition.z;
        }

        auto newRotation = GetTarget()->GetTransform().GetRotationInDegrees();
        if (bufferRotation != newRotation)
        {
            bufferRotation = newRotation;
            rotation[0] = bufferRotation.x;
            rotation[1] = bufferRotation.y;
            rotation[2] = bufferRotation.z;
        }

        auto newScale = GetTarget()->GetTransform().GetScale();
        if (bufferScale != newScale)
        {
            bufferScale = newScale;
            scale[0] = bufferScale.x;
            scale[1] = bufferScale.y;
            scale[2] = bufferScale.z;
        }
    }

    void GameObjectEditor::UpdateFromUI()
    {
        if (GetTarget()->IsActive() != isActive)
        {
            LOG_DEBUG("New Active status ({})", isActive);
            GetTarget()->SetActive(isActive);
        }

        if (bufferPosition.x != position[0] || bufferPosition.y != position[1] || bufferPosition.z != position[2])
        {
            LOG_DEBUG("New Position ({},{},{})", position[0], position[1], position[2]);
            bufferPosition = glm::vec3(position[0], position[1], position[2]);
            GetTarget()->GetTransform().SetPosition(bufferPosition);
        }

        if (bufferRotation.x != rotation[0] || bufferRotation.y != rotation[1] || bufferRotation.z != rotation[2])
        {
            LOG_DEBUG("New Rotation ({},{},{})", rotation[0], rotation[1], rotation[2]);
            bufferRotation = glm::vec3(rotation[0], rotation[1], rotation[2]);
            GetTarget()->GetTransform().SetRotationInDegrees(bufferRotation);
        }

        if (bufferScale.x != scale[0] || bufferScale.y != scale[1] || bufferScale.z != scale[2])
        {
            LOG_DEBUG("New Scale ({},{},{})", scale[0], scale[1], scale[2]);
            bufferScale = glm::vec3(scale[0], scale[1], scale[2]);
            GetTarget()->GetTransform().SetScale(bufferScale);
        }
    }

    const std::string &GameObjectEditor::GetTargetName() const
    {
        return GetTarget()->GetName();
    }

    bool *GameObjectEditor::GetIsActive()
    {
        return &isActive;
    }

    float *GameObjectEditor::GetPosition()
    {
        return position;
    }

    float *GameObjectEditor::GetRotation()
    {
        return rotation;
    }

    float *GameObjectEditor::GetScale()
    {
        return scale;
    }
}