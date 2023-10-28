#include "Engine/Graphics/Elements/Shader.h"
#include "Engine/Tools/Log/Logger.h"
#include "Engine/Tools/Other/Files.h"

namespace Engine::Graphics
{
    Shader::Shader(const std::string &vertexLocation, const std::string &fragmentLocation)
        : Shader(std::make_shared<std::string>(vertexLocation),
            nullptr,
            nullptr,
            nullptr,
            std::make_shared<std::string>(fragmentLocation))
    {}

    Shader::Shader(const std::string &vertexLocation, const std::string &geometryLocation, const std::string &fragmentLocation)
        : Shader(std::make_shared<std::string>(vertexLocation),
            nullptr,
            nullptr,
            std::make_shared<std::string>(geometryLocation),
            std::make_shared<std::string>(fragmentLocation))
    {}

    Shader::Shader(const std::string &vertexLocation, const std::string &tesselationControlLocation, const std::string &tesselationEvaluationLocation, const std::string &fragmentLocation)
        : Shader(std::make_shared<std::string>(vertexLocation),
            std::make_shared<std::string>(tesselationControlLocation),
            std::make_shared<std::string>(tesselationEvaluationLocation),
            nullptr,
            std::make_shared<std::string>(fragmentLocation))
    {}

    Shader::Shader(const std::string &vertexLocation, const std::string &tesselationControlLocation, const std::string &tesselationEvaluationLocation, const std::string &geometryLocation, const std::string &fragmentLocation)
        : Shader(std::make_shared<std::string>(vertexLocation), 
            std::make_shared<std::string>(tesselationControlLocation), 
            std::make_shared<std::string>(tesselationEvaluationLocation), 
            std::make_shared<std::string>(geometryLocation),
            std::make_shared<std::string>(fragmentLocation))
    {}

    Shader::Shader(std::shared_ptr<std::string> vertexLocation, std::shared_ptr<std::string> fragmentLocation)
        : Shader(vertexLocation, nullptr, nullptr, nullptr, fragmentLocation)
    {}
    Shader::Shader(std::shared_ptr<std::string> vertexLocation, std::shared_ptr<std::string> geometryLocation, std::shared_ptr<std::string> fragmentLocation)
        : Shader(vertexLocation, nullptr, nullptr, geometryLocation, fragmentLocation)
    {}
    Shader::Shader(std::shared_ptr<std::string> vertexLocation, std::shared_ptr<std::string> tesselationControlLocation, std::shared_ptr<std::string> tesselationEvaluationLocation, std::shared_ptr<std::string> fragmentLocation)
        : Shader(vertexLocation, tesselationControlLocation, tesselationEvaluationLocation, nullptr, fragmentLocation)
    {}

    Shader::Shader(std::shared_ptr<std::string> vertexLocation, std::shared_ptr<std::string> tesselationControlLocation, std::shared_ptr<std::string> tesselationEvaluationLocation, std::shared_ptr<std::string> geometryLocation, std::shared_ptr<std::string> fragmentLocation)
        : id(0)
    {
        std::shared_ptr<std::string> vertex = nullptr;
        std::shared_ptr<std::string> tesselationControl = nullptr;
        std::shared_ptr<std::string> tesselationEvaluation = nullptr;
        std::shared_ptr<std::string> geometry = nullptr;
        std::shared_ptr<std::string> fragment = nullptr;

        if (vertexLocation)
        {
            vertex = std::make_shared<std::string>(Engine::Tools::Other::ReadRelativeFile(*vertexLocation));
        }
        if (tesselationControlLocation)
        {
            tesselationControl = std::make_shared<std::string>(Engine::Tools::Other::ReadRelativeFile(*tesselationControlLocation));
        }
        if (tesselationEvaluationLocation)
        {
            tesselationEvaluation = std::make_shared<std::string>(Engine::Tools::Other::ReadRelativeFile(*tesselationEvaluationLocation));
        }
        if (geometryLocation)
        {
            geometry = std::make_shared<std::string>(Engine::Tools::Other::ReadRelativeFile(*geometryLocation));
        }
        if (fragmentLocation)
        {
            fragment = std::make_shared<std::string>(Engine::Tools::Other::ReadRelativeFile(*fragmentLocation));
        }
        Create(vertex, tesselationControl, tesselationEvaluation, geometry, fragment);
    }

    Shader::~Shader()
    {
        Clear();
    }

    void Shader::Create(std::shared_ptr<std::string> vertexCode, std::shared_ptr<std::string> tesselationControlCode, std::shared_ptr<std::string> tesselationEvaluationCode, std::shared_ptr<std::string> geometryCode, std::shared_ptr<std::string> fragmentCode)
    {
        id = glCreateProgram();
        if (!id)
        {
            LOG_ERROR("Error creating shader program!");
            return;
        }

        GLuint vertexShader = 0;
        GLuint tesselationControlShader = 0;
        GLuint tesselationEvaluationShader = 0;
        GLuint geometryShader = 0;
        GLuint fragmentShader = 0;

        if (vertexCode)
        {
            vertexShader = AddShader(id, vertexCode, GL_VERTEX_SHADER);
        }
        if (tesselationControlCode)
        {
            tesselationControlShader = AddShader(id, tesselationControlCode, GL_TESS_CONTROL_SHADER);
        }
        if (tesselationEvaluationCode)
        {
            tesselationEvaluationShader = AddShader(id, tesselationEvaluationCode, GL_TESS_EVALUATION_SHADER);
        }
        if (geometryCode)
        {
            geometryShader = AddShader(id, geometryCode, GL_GEOMETRY_SHADER);
        }
        if (fragmentCode)
        {
            fragmentShader = AddShader(id, fragmentCode, GL_FRAGMENT_SHADER);
        }

        LinkProgram();

        if (vertexShader)
        {
            glDeleteShader(vertexShader);
        }
        if (tesselationControlShader)
        {
            glDeleteShader(tesselationControlShader);
        }
        if (tesselationEvaluationShader)
        {
            glDeleteShader(tesselationEvaluationShader);
        }
        if (geometryShader)
        {
            glDeleteShader(geometryShader);
        }
        if (fragmentShader)
        {
            glDeleteShader(fragmentShader);
        }

        GetUniforms();
    }

    GLuint Shader::AddShader(GLuint theProgram, std::shared_ptr<std::string> shaderCode, GLenum shaderType)
    {
        GLuint theShader = glCreateShader(shaderType);

        const GLchar *theCode[1];
        GLint codeLength[1];
        theCode[0] = shaderCode.get()->c_str();
        codeLength[0] = shaderCode.get()->length();
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
    void Shader::GetUniforms()
    {
        uniformModel = glGetUniformLocation(id, "model");
        uniformView = glGetUniformLocation(id, "view");
        uniformProjection = glGetUniformLocation(id, "projection");
        uniformViewProjection = glGetUniformLocation(id, "viewProjection");
        uniformColor = glGetUniformLocation(id, "color");
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
}

