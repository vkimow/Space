#include "Engine/Graphics/Shader.h"
#include "Engine/Tools/Log/Logger.h"
#include "Engine/Tools/Other/Files.h"

namespace Engine::Graphics
{
    Shader::Shader()
        :id(0)
    {}

    Shader::~Shader()
    {
        Clear();
    }

    void Shader::CreateFromFiles(const std::string_view vertexLocation, const std::string_view fragmentLocation)
    {
        std::string vertex = Engine::Tools::Other::ReadRelativeFile(vertexLocation);
        std::string fragment = Engine::Tools::Other::ReadRelativeFile(fragmentLocation);
        Create(std::move(vertex), std::move(fragment));
    }

    void Shader::Create(const std::string_view vertexCode, const std::string_view fragmentCode)
    {
        id = glCreateProgram();
        if (!id)
        {
            LOG_ERROR("Error creating shader program!");
            return;
        }

        GLuint vertexShader = AddShader(id, vertexCode, GL_VERTEX_SHADER);
        GLuint fragmentShader = AddShader(id, fragmentCode, GL_FRAGMENT_SHADER);

        LinkProgram();

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void Shader::Validate()
    {
        GLint result = 0;

        glValidateProgram(id);
        glGetProgramiv(id, GL_VALIDATE_STATUS, &result);
        if (!result)
        {
            GLchar eLog[1024];
            glGetProgramInfoLog(id, sizeof(eLog), NULL, eLog);
            printf("Error validating program: '%s'\n", (char *)eLog);
            return;
        }
    }

    void Shader::Use()
    {
        glUseProgram(id);
    }

    void Shader::Clear()
    {
        if (id != 0)
        {
            glDeleteProgram(id);
            id = 0;
        }
    }

    GLuint Shader::AddShader(GLuint theProgram, const std::string_view shaderCode, GLenum shaderType)
    {
        GLuint theShader = glCreateShader(shaderType);

        const GLchar *theCode[1];
        GLint codeLength[1];
        theCode[0] = shaderCode.data();
        codeLength[0] = shaderCode.size();
        glShaderSource(theShader, 1, theCode, codeLength);

        GLint result = 0;
        glCompileShader(theShader);
        glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
        if (!result)
        {
            GLchar eLog[1024];
            glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
            LOG_ERROR("Error compiling the {} shader: '{}'", shaderType, eLog);
            return 0;
        }

        glAttachShader(theProgram, theShader);
        return theShader;
    }

    void Shader::LinkProgram()
    {
        GLint result = 0;
        glLinkProgram(id);
        glGetProgramiv(id, GL_LINK_STATUS, &result);
        if (!result)
        {
            GLchar eLog[1024];
            glGetProgramInfoLog(id, sizeof(eLog), NULL, eLog);
            LOG_ERROR("Error linking program: {}", eLog);
            return;
        }
    }
}

