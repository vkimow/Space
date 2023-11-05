#include "Engine/Graphics/Elements/ModelMatrix/ModelMatrixFromMatrix.h"

namespace Engine::Graphics
{
    TransformMatrixFromMatrix::TransformMatrixFromMatrix(const glm::mat4 &matrix)
        : matrix(matrix)
    {}

    TransformMatrixFromMatrix::TransformMatrixFromMatrix(glm::mat4 &&matrix)
        : matrix(std::move(matrix))
    {}

    TransformMatrixFromMatrix::TransformMatrixFromMatrix(const TransformMatrixFromMatrix & rhs)
        : matrix(rhs.matrix)
    {}

    TransformMatrixFromMatrix::TransformMatrixFromMatrix(TransformMatrixFromMatrix &&rhs) noexcept
        : matrix(std::move(rhs.matrix))
    {}

    TransformMatrixFromMatrix &TransformMatrixFromMatrix::operator=(const TransformMatrixFromMatrix & rhs)
    {
        matrix = rhs.matrix;
        return *this;
    }

    TransformMatrixFromMatrix &TransformMatrixFromMatrix::operator=(TransformMatrixFromMatrix &&rhs) noexcept
    {
        matrix = std::move(rhs.matrix);
        return *this;
    }

    const glm::mat4 &TransformMatrixFromMatrix::GetModelMatrix() const
    {
        return matrix;
    }

    void TransformMatrixFromMatrix::Use(Shader *shader)
    {
        shader->SetMatrix4("Model", matrix);
    }
}