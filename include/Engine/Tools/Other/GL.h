#pragma once
#include <GL/glew.h>

namespace Engine::Tools::Graphics
{
    void ClearFramebuffer(GLuint &value);
    void ClearRenderbuffer(GLuint &value);
    void ClearTexture(GLuint &value);
    void ClearVertexArray(GLuint &value);
    void ClearBuffer(GLuint &value);
}