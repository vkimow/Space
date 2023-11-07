#include "Engine/Graphics/Elements/Shader.h"
#include "Engine/Tools/Log/Logger.h"
#include "Engine/Tools/Other/Files.h"
#include <glm/gtc/type_ptr.hpp>
#include <regex>
#include "Engine/Graphics/Elements/Container.h"

namespace Engine::Graphics
{
    Shader::Shader(const std::string &vertexCode, const std::string &fragmentCode)
        : Shader(std::make_shared<std::string>(vertexCode),
            nullptr,
            nullptr,
            nullptr,
            std::make_shared<std::string>(fragmentCode))
    {}

    Shader::Shader(const std::string &vertexCode, const std::string &geometryCode, const std::string &fragmentCode)
        : Shader(std::make_shared<std::string>(vertexCode),
            nullptr,
            nullptr,
            std::make_shared<std::string>(geometryCode),
            std::make_shared<std::string>(fragmentCode))
    {}

    Shader::Shader(const std::string &vertexCode, const std::string &tesselationControlCode, const std::string &tesselationEvaluationCode, const std::string &fragmentCode)
        : Shader(std::make_shared<std::string>(vertexCode),
            std::make_shared<std::string>(tesselationControlCode),
            std::make_shared<std::string>(tesselationEvaluationCode),
            nullptr,
            std::make_shared<std::string>(fragmentCode))
    {}

    Shader::Shader(const std::string &vertexCode, const std::string &tesselationControlCode, const std::string &tesselationEvaluationCode, const std::string &geometryCode, const std::string &fragmentCode)
        : Shader(std::make_shared<std::string>(vertexCode),
            std::make_shared<std::string>(tesselationControlCode),
            std::make_shared<std::string>(tesselationEvaluationCode),
            std::make_shared<std::string>(geometryCode),
            std::make_shared<std::string>(fragmentCode))
    {}

    Shader::Shader(std::shared_ptr<std::string> vertexCode, std::shared_ptr<std::string> fragmentCode)
        : Shader(vertexCode, nullptr, nullptr, nullptr, fragmentCode)
    {}
    Shader::Shader(std::shared_ptr<std::string> vertexCode, std::shared_ptr<std::string> geometryCode, std::shared_ptr<std::string> fragmentCode)
        : Shader(vertexCode, nullptr, nullptr, geometryCode, fragmentCode)
    {}
    Shader::Shader(std::shared_ptr<std::string> vertexCode, std::shared_ptr<std::string> tesselationControlCode, std::shared_ptr<std::string> tesselationEvaluationCode, std::shared_ptr<std::string> fragmentCode)
        : Shader(vertexCode, tesselationControlCode, tesselationEvaluationCode, nullptr, fragmentCode)
    {}

    Shader::Shader(std::shared_ptr<std::string> vertexCode, std::shared_ptr<std::string> tesselationControlCode, std::shared_ptr<std::string> tesselationEvaluationCode, std::shared_ptr<std::string> geometryCode, std::shared_ptr<std::string> fragmentCode)
        : id(0)
        , uniforms()
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
    }

    Shader::~Shader()
    {
        Clear();
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

    void Shader::Disable()
    {
        glUseProgram(0);
    }

    void Shader::Clear()
    {
        if (id != 0)
        {
            glDeleteProgram(id);
            id = 0;
        }
    }

    void Shader::SetFloat(const std::string &name, GLfloat value)
    {
        glUniform1f(GetUniform(name), value);
    }

    void Shader::SetFloat(const std::string &name, size_t count, GLfloat *values)
    {
        glUniform1fv(GetUniform(name), count, values);
    }

    void Shader::SetInt(const std::string &name, GLint value)
    {
        glUniform1i(GetUniform(name), value);
    }

    void Shader::SetInt(const std::string &name, size_t count, GLint *values)
    {
        glUniform1iv(GetUniform(name), count, values);
    }

    void Shader::SetUnsigned(const std::string &name, GLuint value)
    {
        glUniform1ui(GetUniform(name), value);
    }

    void Shader::SetUnsigned(const std::string &name, size_t count, GLuint *values)
    {
        glUniform1uiv(GetUniform(name), count, values);
    }

    void Shader::SetVector2f(const std::string &name, GLfloat x, GLfloat y)
    {
        glUniform2f(GetUniform(name), x, y);
    }

    void Shader::SetVector2f(const std::string &name, const glm::vec<2, GLfloat> &value)
    {
        glUniform2fv(GetUniform(name), 1, glm::value_ptr(value));
    }

    void Shader::SetVector2f(const std::string &name, size_t count, glm::vec<2, GLfloat> *values)
    {
        SetVector2f(name, count, glm::value_ptr(*values));
    }

    void Shader::SetVector2f(const std::string & name, size_t count, GLfloat * values)
    {
        glUniform2fv(GetUniform(name), count, values);
    }

    void Shader::SetVector2i(const std::string &name, GLint x, GLint y)
    {
        glUniform2i(GetUniform(name), x, y);
    }

    void Shader::SetVector2i(const std::string &name, const glm::vec<2, GLint> &value)
    {
        glUniform2iv(GetUniform(name), 1, glm::value_ptr(value));
    }

    void Shader::SetVector2i(const std::string &name, size_t count, glm::vec<2, GLint> *values)
    {
        SetVector2i(name, count, glm::value_ptr(*values));
    }

    void Shader::SetVector2i(const std::string & name, size_t count, GLint * values)
    {
        glUniform2iv(GetUniform(name), count, values);
    }

    void Shader::SetVector2u(const std::string &name, GLuint x, GLuint y)
    {
        glUniform2ui(GetUniform(name), x, y);
    }

    void Shader::SetVector2u(const std::string &name, const glm::vec<2, GLuint> &value)
    {
        glUniform2uiv(GetUniform(name), 1, glm::value_ptr(value));
    }

    void Shader::SetVector2u(const std::string &name, size_t count, glm::vec<2, GLuint> *values)
    {
        SetVector2u(name, count, glm::value_ptr(*values));
    }

    void Shader::SetVector2u(const std::string & name, size_t count, GLuint * values)
    {
        glUniform2uiv(GetUniform(name), count, values);
    }

    void Shader::SetVector3f(const std::string &name, GLfloat x, GLfloat y, GLfloat z)
    {
        glUniform3f(GetUniform(name), x, y, z);
    }

    void Shader::SetVector3f(const std::string &name, const glm::vec<3, GLfloat> &value)
    {
        glUniform3fv(GetUniform(name), 1, glm::value_ptr(value));
    }

    void Shader::SetVector3f(const std::string &name, size_t count, glm::vec<3, GLfloat> *values)
    {
        SetVector3f(name, count, glm::value_ptr(*values));
    }

    void Shader::SetVector3f(const std::string & name, size_t count, GLfloat * values)
    {
        glUniform3fv(GetUniform(name), count, values);
    }

    void Shader::SetVector3i(const std::string &name, GLint x, GLint y, GLint z)
    {
        glUniform3i(GetUniform(name), x, y, z);
    }

    void Shader::SetVector3i(const std::string &name, const glm::vec<3, GLint> &value)
    {
        glUniform3iv(GetUniform(name), 1, glm::value_ptr(value));
    }

    void Shader::SetVector3i(const std::string &name, size_t count, glm::vec<3, GLint> *values)
    {
        SetVector3i(name, count, glm::value_ptr(*values));
    }

    void Shader::SetVector3i(const std::string & name, size_t count, GLint * values)
    {
        glUniform3iv(GetUniform(name), count, values);
    }

    void Shader::SetVector3u(const std::string &name, GLuint x, GLuint y, GLuint z)
    {
        glUniform3ui(GetUniform(name), x, y, z);
    }

    void Shader::SetVector3u(const std::string &name, const glm::vec<3, GLuint> &value)
    {
        glUniform3uiv(GetUniform(name), 1, glm::value_ptr(value));
    }

    void Shader::SetVector3u(const std::string &name, size_t count, glm::vec<3, GLuint> *values)
    {
        SetVector3u(name, count, glm::value_ptr(*values));
    }

    void Shader::SetVector3u(const std::string & name, size_t count, GLuint * values)
    {
        glUniform3uiv(GetUniform(name), count, values);
    }

    void Shader::SetVector4f(const std::string &name, GLfloat w, GLfloat x, GLfloat y, GLfloat z)
    {
        glUniform4f(GetUniform(name), w, x, y, z);
    }

    void Shader::SetVector4f(const std::string &name, const glm::vec<4, GLfloat> &value)
    {
        glUniform4fv(GetUniform(name), 1, glm::value_ptr(value));
    }

    void Shader::SetVector4f(const std::string &name, size_t count, glm::vec<4, GLfloat> *values)
    {
        SetVector4f(name, count, glm::value_ptr(*values));
    }

    void Shader::SetVector4f(const std::string & name, size_t count, GLfloat * values)
    {
        glUniform4fv(GetUniform(name), count, values);
    }

    void Shader::SetVector4i(const std::string &name, GLint w, GLint x, GLint y, GLint z)
    {
        glUniform4i(GetUniform(name), w, x, y, z);
    }

    void Shader::SetVector4i(const std::string &name, const glm::vec<4, GLint> &value)
    {
        glUniform4iv(GetUniform(name), 1, glm::value_ptr(value));
    }

    void Shader::SetVector4i(const std::string &name, size_t count, glm::vec<4, GLint> *values)
    {
        SetVector4i(name, count, glm::value_ptr(*values));
    }

    void Shader::SetVector4i(const std::string & name, size_t count, GLint * values)
    {
        glUniform4iv(GetUniform(name), count, values);
    }

    void Shader::SetVector4u(const std::string &name, GLuint w, GLuint x, GLuint y, GLuint z)
    {
        glUniform4ui(GetUniform(name), w, x, y, z);
    }

    void Shader::SetVector4u(const std::string &name, const glm::vec<4, GLuint> &value)
    {
        glUniform4uiv(GetUniform(name), 1, glm::value_ptr(value));
    }

    void Shader::SetVector4u(const std::string &name, size_t count, glm::vec<4, GLuint> *values)
    {
        SetVector4u(name, count, glm::value_ptr(*values));
    }

    void Shader::SetVector4u(const std::string & name, size_t count, GLuint * values)
    {
        glUniform4uiv(GetUniform(name), count, values);
    }

    void Shader::SetMatrix4(const std::string &name, const glm::mat4 &value)
    {
        glUniformMatrix4fv(GetUniform(name), 1, GL_FALSE, glm::value_ptr(value));
    }

    void Shader::SetMatrix4(const std::string &name, size_t count, glm::mat4 *values)
    {
        glUniformMatrix4fv(GetUniform(name), count, GL_FALSE, glm::value_ptr(*values));
    }

    void Shader::SetMatrix4(const std::string & name, size_t count, GLfloat * values)
    {
        glUniformMatrix4fv(GetUniform(name), 1, GL_FALSE, values);
    }

    void Shader::SetFloat(GLuint uniform, GLfloat value) const
    {
        glUniform1f(uniform, value);
    }

    void Shader::SetFloat(GLuint uniform, size_t count, GLfloat *values) const
    {
        glUniform1fv(uniform, count, values);
    }

    void Shader::SetInt(GLuint uniform, GLint value) const
    {
        glUniform1i(uniform, value);
    }

    void Shader::SetInt(GLuint uniform, size_t count, GLint *values) const
    {
        glUniform1iv(uniform, count, values);
    }

    void Shader::SetUnsigned(GLuint uniform, GLuint value) const
    {
        glUniform1ui(uniform, value);
    }

    void Shader::SetUnsigned(GLuint uniform, size_t count, GLuint *values) const
    {
        glUniform1uiv(uniform, count, values);
    }

    void Shader::SetVector2f(GLuint uniform, GLfloat x, GLfloat y) const
    {
        glUniform2f(uniform, x, y);
    }

    void Shader::SetVector2f(GLuint uniform, const glm::vec<2, GLfloat> &value) const
    {
        glUniform2fv(uniform, 1, glm::value_ptr(value));
    }

    void Shader::SetVector2f(GLuint uniform, size_t count, glm::vec<2, GLfloat> *values) const
    {
        SetVector2f(uniform, count, glm::value_ptr(*values));
    }

    void Shader::SetVector2f(GLuint uniform, size_t count, GLfloat *values) const
    {
        glUniform2fv(uniform, count, values);
    }

    void Shader::SetVector2i(GLuint uniform, GLint x, GLint y) const
    {
        glUniform2i(uniform, x, y);
    }

    void Shader::SetVector2i(GLuint uniform, const glm::vec<2, GLint> &value) const
    {
        glUniform2iv(uniform, 1, glm::value_ptr(value));
    }

    void Shader::SetVector2i(GLuint uniform, size_t count, glm::vec<2, GLint> *values) const
    {
        SetVector2i(uniform, count, glm::value_ptr(*values));
    }

    void Shader::SetVector2i(GLuint uniform, size_t count, GLint *values) const
    {
        glUniform2iv(uniform, count, values);
    }

    void Shader::SetVector2u(GLuint uniform, GLuint x, GLuint y) const
    {
        glUniform2ui(uniform, x, y);
    }

    void Shader::SetVector2u(GLuint uniform, const glm::vec<2, GLuint> &value) const
    {
        glUniform2uiv(uniform, 1, glm::value_ptr(value));
    }

    void Shader::SetVector2u(GLuint uniform, size_t count, glm::vec<2, GLuint> *values) const
    {
        SetVector2u(uniform, count, glm::value_ptr(*values));
    }

    void Shader::SetVector2u(GLuint uniform, size_t count, GLuint *values) const
    {
        glUniform2uiv(uniform, count, values);
    }

    void Shader::SetVector3f(GLuint uniform, GLfloat x, GLfloat y, GLfloat z) const
    {
        glUniform3f(uniform, x, y, z);
    }

    void Shader::SetVector3f(GLuint uniform, const glm::vec<3, GLfloat> &value) const
    {
        glUniform3fv(uniform, 1, glm::value_ptr(value));
    }

    void Shader::SetVector3f(GLuint uniform, size_t count, glm::vec<3, GLfloat> *values) const
    {
        SetVector3f(uniform, count, glm::value_ptr(*values));
    }

    void Shader::SetVector3f(GLuint uniform, size_t count, GLfloat *values) const
    {
        glUniform3fv(uniform, count, values);
    }

    void Shader::SetVector3i(GLuint uniform, GLint x, GLint y, GLint z) const
    {
        glUniform3i(uniform, x, y, z);
    }

    void Shader::SetVector3i(GLuint uniform, const glm::vec<3, GLint> &value) const
    {
        glUniform3iv(uniform, 1, glm::value_ptr(value));
    }

    void Shader::SetVector3i(GLuint uniform, size_t count, glm::vec<3, GLint> *values) const
    {
        SetVector3i(uniform, count, glm::value_ptr(*values));
    }

    void Shader::SetVector3i(GLuint uniform, size_t count, GLint *values) const
    {
        glUniform3iv(uniform, count, values);
    }

    void Shader::SetVector3u(GLuint uniform, GLuint x, GLuint y, GLuint z) const
    {
        glUniform3ui(uniform, x, y, z);
    }

    void Shader::SetVector3u(GLuint uniform, const glm::vec<3, GLuint> &value) const
    {
        glUniform3uiv(uniform, 1, glm::value_ptr(value));
    }

    void Shader::SetVector3u(GLuint uniform, size_t count, glm::vec<3, GLuint> *values) const
    {
        SetVector3u(uniform, count, glm::value_ptr(*values));
    }

    void Shader::SetVector3u(GLuint uniform, size_t count, GLuint *values) const
    {
        glUniform3uiv(uniform, count, values);
    }

    void Shader::SetVector4f(GLuint uniform, GLfloat w, GLfloat x, GLfloat y, GLfloat z) const
    {
        glUniform4f(uniform, w, x, y, z);
    }

    void Shader::SetVector4f(GLuint uniform, const glm::vec<4, GLfloat> &value) const
    {
        glUniform4fv(uniform, 1, glm::value_ptr(value));
    }

    void Shader::SetVector4f(GLuint uniform, size_t count, glm::vec<4, GLfloat> *values) const
    {
        SetVector4f(uniform, count, glm::value_ptr(*values));
    }

    void Shader::SetVector4f(GLuint uniform, size_t count, GLfloat *values) const
    {
        glUniform4fv(uniform, count, values);
    }

    void Shader::SetVector4i(GLuint uniform, GLint w, GLint x, GLint y, GLint z) const
    {
        glUniform4i(uniform, w, x, y, z);
    }

    void Shader::SetVector4i(GLuint uniform, const glm::vec<4, GLint> &value) const
    {
        glUniform4iv(uniform, 1, glm::value_ptr(value));
    }

    void Shader::SetVector4i(GLuint uniform, size_t count, glm::vec<4, GLint> *values) const
    {
        SetVector4i(uniform, count, glm::value_ptr(*values));
    }

    void Shader::SetVector4i(GLuint uniform, size_t count, GLint *values) const
    {
        glUniform4iv(uniform, count, values);
    }

    void Shader::SetVector4u(GLuint uniform, GLuint w, GLuint x, GLuint y, GLuint z) const
    {
        glUniform4ui(uniform, w, x, y, z);
    }

    void Shader::SetVector4u(GLuint uniform, const glm::vec<4, GLuint> &value) const
    {
        glUniform4uiv(uniform, 1, glm::value_ptr(value));
    }

    void Shader::SetVector4u(GLuint uniform, size_t count, glm::vec<4, GLuint> *values) const
    {
        SetVector4u(uniform, count, glm::value_ptr(*values));
    }

    void Shader::SetVector4u(GLuint uniform, size_t count, GLuint *values) const
    {
        glUniform4uiv(uniform, count, values);
    }

    void Shader::SetMatrix4(GLuint uniform, const glm::mat4 &value) const
    {
        glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(value));
    }

    void Shader::SetMatrix4(GLuint uniform, size_t count, glm::mat4 *values) const
    {
        glUniformMatrix4fv(uniform, count, GL_FALSE, glm::value_ptr(*values));
    }

    void Shader::SetMatrix4(GLuint uniform, size_t count, GLfloat *values) const
    {
        glUniformMatrix4fv(uniform, 1, GL_FALSE, values);
    }

    GLuint Shader::GetUniform(const std::string &name, bool save)
    {
        if (!uniforms.contains(name))
        {
            if (save)
            {
                uniforms.emplace(name, glGetUniformLocation(id, name.c_str()));
            }
            else
            {
                return glGetUniformLocation(id, name.c_str());
            }
        }

        return uniforms[name];
    }

    Shader *CreateShaderFromFile(Container *const container, const std::string &name, const std::string &vertexLocation, const std::string &fragmentLocation)
    {
        return CreateShaderFromFile(container, name,
            std::make_shared<std::string>(vertexLocation),
            nullptr,
            nullptr,
            nullptr,
            std::make_shared<std::string>(fragmentLocation)
        );
    }

    Shader *CreateShaderFromFile(Container *const container, const std::string &name, const std::string &vertexLocation, const std::string &geometryLocation, const std::string &fragmentLocation)
    {
        return CreateShaderFromFile(container, name,
            std::make_shared<std::string>(vertexLocation),
            nullptr,
            nullptr,
            std::make_shared<std::string>(geometryLocation),
            std::make_shared<std::string>(fragmentLocation)
        );
    }

    Shader *CreateShaderFromFile(Container *const container, const std::string &name, const std::string &vertexLocation, const std::string &tesselationControlLocation, const std::string &tesselationEvaluationLocation, const std::string &fragmentLocation)
    {
        return CreateShaderFromFile(container, name,
            std::make_shared<std::string>(vertexLocation),
            std::make_shared<std::string>(tesselationControlLocation),
            std::make_shared<std::string>(tesselationEvaluationLocation),
            nullptr,
            std::make_shared<std::string>(fragmentLocation)
        );
    }

    Shader *CreateShaderFromFile(Container *const container, const std::string &name, const std::string &vertexLocation, const std::string &tesselationControlLocation, const std::string &tesselationEvaluationLocation, const std::string &geometryLocation, const std::string &fragmentLocation)
    {
        return CreateShaderFromFile(container, name,
            std::make_shared<std::string>(vertexLocation),
            std::make_shared<std::string>(tesselationControlLocation),
            std::make_shared<std::string>(tesselationEvaluationLocation),
            std::make_shared<std::string>(geometryLocation),
            std::make_shared<std::string>(fragmentLocation)
        );
    }

    Shader *CreateShaderFromFile(Container *const container, const std::string &name, std::shared_ptr<std::string> vertexLocation, std::shared_ptr<std::string> fragmentLocation)
    {
        return CreateShaderFromFile(container, name,
            vertexLocation,
            nullptr,
            nullptr,
            nullptr,
            fragmentLocation
        );
    }

    Shader *CreateShaderFromFile(Container *const container, const std::string &name, std::shared_ptr<std::string> vertexLocation, std::shared_ptr<std::string> geometryLocation, std::shared_ptr<std::string> fragmentLocation)
    {
        return CreateShaderFromFile(container, name,
            vertexLocation,
            nullptr,
            nullptr,
            geometryLocation,
            fragmentLocation
        );
    }

    Shader *CreateShaderFromFile(Container *const container, const std::string &name, std::shared_ptr<std::string> vertexLocation, std::shared_ptr<std::string> tesselationControlLocation, std::shared_ptr<std::string> tesselationEvaluationLocation, std::shared_ptr<std::string> fragmentLocation)
    {
        return CreateShaderFromFile(container, name,
            vertexLocation,
            tesselationControlLocation,
            tesselationEvaluationLocation,
            nullptr,
            fragmentLocation
        );
    }

    Shader *CreateShaderFromFile(Container *const container, const std::string &name, std::shared_ptr<std::string> vertexLocation, std::shared_ptr<std::string> tesselationControlLocation, std::shared_ptr<std::string> tesselationEvaluationLocation, std::shared_ptr<std::string> geometryLocation, std::shared_ptr<std::string> fragmentLocation)
    {
        std::shared_ptr<std::string> vertex = nullptr;
        std::shared_ptr<std::string> tesselationControl = nullptr;
        std::shared_ptr<std::string> tesselationEvaluation = nullptr;
        std::shared_ptr<std::string> geometry = nullptr;
        std::shared_ptr<std::string> fragment = nullptr;

        if (vertexLocation)
        {
            vertex = std::make_shared<std::string>(Engine::Tools::Files::ReadRelativeFile(*vertexLocation));
        }
        if (tesselationControlLocation)
        {
            tesselationControl = std::make_shared<std::string>(Engine::Tools::Files::ReadRelativeFile(*tesselationControlLocation));
        }
        if (tesselationEvaluationLocation)
        {
            tesselationEvaluation = std::make_shared<std::string>(Engine::Tools::Files::ReadRelativeFile(*tesselationEvaluationLocation));
        }
        if (geometryLocation)
        {
            geometry = std::make_shared<std::string>(Engine::Tools::Files::ReadRelativeFile(*geometryLocation));
        }
        if (fragmentLocation)
        {
            fragment = std::make_shared<std::string>(Engine::Tools::Files::ReadRelativeFile(*fragmentLocation));
        }
        return container->AddShader(name, vertex, tesselationControl, tesselationEvaluation, geometry, fragment);
    }
}

