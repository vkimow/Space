#include "Engine/Graphics/Elements/ModelMatrix/ModelMatrixFromTransformPtr.h"
#include "Engine/Tools/Log/Logger.h"

namespace Engine::Graphics
{
    TransformMatrixFromTransformPtr::TransformMatrixFromTransformPtr(Objects::Transform *transform)
        : transform(transform)
    {
        if (!transform)
        {
            LOG_ERROR("Transform is null");
        }
    }

    TransformMatrixFromTransformPtr::TransformMatrixFromTransformPtr(const TransformMatrixFromTransformPtr & rhs)
        : transform(rhs.transform)
    {
        if (!transform)
        {
            LOG_ERROR("Transform is null");
        }
    }

    TransformMatrixFromTransformPtr::TransformMatrixFromTransformPtr(TransformMatrixFromTransformPtr && rhs) noexcept
        : transform(rhs.transform)
    {
        if (!transform)
        {
            LOG_ERROR("Transform is null");
        }

        rhs.transform = nullptr;
    }

    TransformMatrixFromTransformPtr &TransformMatrixFromTransformPtr::operator=(const TransformMatrixFromTransformPtr & rhs)
    {
        transform = rhs.transform;
        return *this;
    }

    TransformMatrixFromTransformPtr &TransformMatrixFromTransformPtr::operator=(TransformMatrixFromTransformPtr &&rhs) noexcept
    {
        transform = rhs.transform;
        rhs.transform = nullptr;
        return *this;
    }

    const glm::mat4 &TransformMatrixFromTransformPtr::GetModelMatrix() const
    {
        return transform->GetTransformMatrix();
    }

    void TransformMatrixFromTransformPtr::Use(Shader *shader)
    {
        shader->SetMatrix4("Model", transform->GetTransformMatrix());
    }
}