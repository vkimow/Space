#include "Engine/Tools/Other/GL.h"

namespace Engine::Tools::Graphics
{
    void ClearFramebuffer(GLuint &value)
    {
        if (value != 0)
        {
            glDeleteFramebuffers(1, &value);
            value = 0;
        }
    }

    void ClearRenderbuffer(GLuint &value)
    {
        if (value != 0)
        {
            glDeleteRenderbuffers(1, &value);
            value = 0;
        }
    }

    void ClearTexture(GLuint &value)
    {
        if (value != 0)
        {
            glDeleteTextures(1, &value);
            value = 0;
        }
    }

    void ClearVertexArray(GLuint &value)
    {
        if (value != 0)
        {
            glDeleteVertexArrays(1, &value);
            value = 0;
        }
    }

    void ClearBuffer(GLuint & value)
    {
        if (value != 0)
        {
            glDeleteBuffers(1, &value);
            value = 0;
        }
    }
}