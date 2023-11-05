#pragma once

#include "Engine/Graphics/Elements/Interfaces/IModelMatrix.h"
#include "Engine/Objects/Transform.h"

namespace Engine::Graphics
{
    class TransformMatrixFromTransformPtr: public IModelMatrix
    {
    public:
        TransformMatrixFromTransformPtr() = delete;
        TransformMatrixFromTransformPtr(Objects::Transform* transform);
        TransformMatrixFromTransformPtr(const TransformMatrixFromTransformPtr &rhs);
        TransformMatrixFromTransformPtr(TransformMatrixFromTransformPtr &&rhs) noexcept;
        TransformMatrixFromTransformPtr &operator=(const TransformMatrixFromTransformPtr &rhs);
        TransformMatrixFromTransformPtr &operator=(TransformMatrixFromTransformPtr &&rhs) noexcept;
        ~TransformMatrixFromTransformPtr() = default;

        const glm::mat4 &GetModelMatrix() const override final;
        void Use(Shader *shader) override final;

    private:
        Objects::Transform * transform;
    };
}