#pragma once

#include "Engine/Graphics/Elements/Interfaces/IModelMatrix.h"

namespace Engine::Graphics
{
    class TransformMatrixFromMatrix: public IModelMatrix
    {
    public:
        TransformMatrixFromMatrix() = delete;
        TransformMatrixFromMatrix(const glm::mat4 &matrix);
        TransformMatrixFromMatrix(glm::mat4 &&matrix);
        TransformMatrixFromMatrix(const TransformMatrixFromMatrix &rhs);
        TransformMatrixFromMatrix(TransformMatrixFromMatrix &&rhs) noexcept;
        TransformMatrixFromMatrix &operator=(const TransformMatrixFromMatrix &rhs);
        TransformMatrixFromMatrix &operator=(TransformMatrixFromMatrix &&rhs) noexcept;
        ~TransformMatrixFromMatrix() = default;

        const glm::mat4 &GetModelMatrix() const override final;
        void Use(Shader *shader) override final;

    private:
        glm::mat4 matrix;
    };
}