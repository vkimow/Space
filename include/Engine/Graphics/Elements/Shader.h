#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <unordered_map>

namespace Engine::Graphics
{
    class Container;
    class Shader
    {
        friend class Container;

    private:
        Shader() = delete;
        Shader(const std::string &vertexCode, const std::string &fragmentCode);
        Shader(const std::string &vertexCode, const std::string &geometryCode, const std::string &fragmentCode);
        Shader(const std::string &vertexCode, const std::string &tesselationControlCode, const std::string &tesselationEvaluationCode, const std::string &fragmentCode);
        Shader(const std::string &vertexCode, const std::string &tesselationControlCode, const std::string &tesselationEvaluationCode, const std::string &geometryCode, const std::string &fragmentCode);
        Shader(std::shared_ptr<std::string> vertexCode, std::shared_ptr<std::string> fragmentCode);
        Shader(std::shared_ptr<std::string> vertexCode, std::shared_ptr<std::string> geometryCode, std::shared_ptr<std::string> fragmentCode);
        Shader(std::shared_ptr<std::string> vertexCode, std::shared_ptr<std::string> tesselationControlCode, std::shared_ptr<std::string> tesselationEvaluationCode, std::shared_ptr<std::string> fragmentCode);
        Shader(std::shared_ptr<std::string> vertexCode, std::shared_ptr<std::string> tesselationControlCode, std::shared_ptr<std::string>  tesselationEvaluationCode, std::shared_ptr<std::string>  geometryCode, std::shared_ptr<std::string> fragmentCode);
        Shader(const Shader &rhs) = delete;
        Shader(Shader &&rhs) = delete;
        Shader &operator=(const Shader &rhs) = delete;
        Shader &operator=(Shader &&rhs) = delete;
        ~Shader();

    private:
        GLuint AddShader(GLuint theProgram, std::shared_ptr<std::string> shaderCode, GLenum shaderType);
        void LinkProgram();

    public:
        void Validate();
        void Use();
        void Disable();
        void Clear();

    public:
        void SetFloat(const std::string &name, GLfloat value);
        void SetFloat(const std::string &name, size_t count, GLfloat *values);
        void SetInt(const std::string &name, GLint value);
        void SetInt(const std::string &name, size_t count, GLint *values);
        void SetUnsigned(const std::string &name, GLuint value);
        void SetUnsigned(const std::string &name, size_t count, GLuint *values);

        void SetVector2f(const std::string &name, GLfloat x, GLfloat y);
        void SetVector2f(const std::string &name, const glm::vec<2, GLfloat> &value);
        void SetVector2f(const std::string &name, size_t count, glm::vec<2, GLfloat> *values);
        void SetVector2f(const std::string &name, size_t count, GLfloat *values);
        void SetVector2i(const std::string &name, GLint x, GLint y);
        void SetVector2i(const std::string &name, const glm::vec<2, GLint> &value);
        void SetVector2i(const std::string &name, size_t count, glm::vec<2, GLint> *values);
        void SetVector2i(const std::string &name, size_t count, GLint *values);
        void SetVector2u(const std::string &name, GLuint x, GLuint y);
        void SetVector2u(const std::string &name, const glm::vec<2, GLuint> &value);
        void SetVector2u(const std::string &name, size_t count, glm::vec<2, GLuint> *values);
        void SetVector2u(const std::string &name, size_t count, GLuint *values);

        void SetVector3f(const std::string &name, GLfloat x, GLfloat y, GLfloat z);
        void SetVector3f(const std::string &name, const glm::vec<3, GLfloat> &value);
        void SetVector3f(const std::string &name, size_t count, glm::vec<3, GLfloat> *values);
        void SetVector3f(const std::string &name, size_t count, GLfloat *values);
        void SetVector3i(const std::string &name, GLint x, GLint y, GLint z);
        void SetVector3i(const std::string &name, const glm::vec<3, GLint> &value);
        void SetVector3i(const std::string &name, size_t count, glm::vec<3, GLint> *values);
        void SetVector3i(const std::string &name, size_t count, GLint *values);
        void SetVector3u(const std::string &name, GLuint x, GLuint y, GLuint z);
        void SetVector3u(const std::string &name, const glm::vec<3, GLuint> &value);
        void SetVector3u(const std::string &name, size_t count, glm::vec<3, GLuint> *values);
        void SetVector3u(const std::string &name, size_t count, GLuint *values);

        void SetVector4f(const std::string &name, GLfloat w, GLfloat x, GLfloat y, GLfloat z);
        void SetVector4f(const std::string &name, const glm::vec<4, GLfloat> &value);
        void SetVector4f(const std::string &name, size_t count, glm::vec<4, GLfloat> *values);
        void SetVector4f(const std::string &name, size_t count, GLfloat *values);
        void SetVector4i(const std::string &name, GLint w, GLint x, GLint y, GLint z);
        void SetVector4i(const std::string &name, const glm::vec<4, GLint> &value);
        void SetVector4i(const std::string &name, size_t count, glm::vec<4, GLint> *values);
        void SetVector4i(const std::string &name, size_t count, GLint *values);
        void SetVector4u(const std::string &name, GLuint w, GLuint x, GLuint y, GLuint z);
        void SetVector4u(const std::string &name, const glm::vec<4, GLuint> &value);
        void SetVector4u(const std::string &name, size_t count, glm::vec<4, GLuint> *values);
        void SetVector4u(const std::string &name, size_t count, GLuint *values);

        void SetMatrix4(const std::string &name, const glm::mat4 &matrix);
        void SetMatrix4(const std::string &name, size_t count, glm::mat4 *values);
        void SetMatrix4(const std::string &name, size_t count, GLfloat *values);


        void SetFloat(GLuint uniform, GLfloat value) const;
        void SetFloat(GLuint uniform, size_t count, GLfloat *values) const;
        void SetInt(GLuint uniform, GLint value) const;
        void SetInt(GLuint uniform, size_t count, GLint *values) const;
        void SetUnsigned(GLuint uniform, GLuint value) const;
        void SetUnsigned(GLuint uniform, size_t count, GLuint *values) const;

        void SetVector2f(GLuint uniform, GLfloat x, GLfloat y) const;
        void SetVector2f(GLuint uniform, const glm::vec<2, GLfloat> &value) const;
        void SetVector2f(GLuint uniform, size_t count, glm::vec<2, GLfloat> *values) const;
        void SetVector2f(GLuint uniform, size_t count, GLfloat *values) const;
        void SetVector2i(GLuint uniform, GLint x, GLint y) const;
        void SetVector2i(GLuint uniform, const glm::vec<2, GLint> &value) const;
        void SetVector2i(GLuint uniform, size_t count, glm::vec<2, GLint> *values) const;
        void SetVector2i(GLuint uniform, size_t count, GLint *values) const;
        void SetVector2u(GLuint uniform, GLuint x, GLuint y) const;
        void SetVector2u(GLuint uniform, const glm::vec<2, GLuint> &value) const;
        void SetVector2u(GLuint uniform, size_t count, glm::vec<2, GLuint> *values) const;
        void SetVector2u(GLuint uniform, size_t count, GLuint *values) const;

        void SetVector3f(GLuint uniform, GLfloat x, GLfloat y, GLfloat z) const;
        void SetVector3f(GLuint uniform, const glm::vec<3, GLfloat> &value) const;
        void SetVector3f(GLuint uniform, size_t count, glm::vec<3, GLfloat> *values) const;
        void SetVector3f(GLuint uniform, size_t count, GLfloat *values) const;
        void SetVector3i(GLuint uniform, GLint x, GLint y, GLint z) const;
        void SetVector3i(GLuint uniform, const glm::vec<3, GLint> &value) const;
        void SetVector3i(GLuint uniform, size_t count, glm::vec<3, GLint> *values) const;
        void SetVector3i(GLuint uniform, size_t count, GLint *values) const;
        void SetVector3u(GLuint uniform, GLuint x, GLuint y, GLuint z) const;
        void SetVector3u(GLuint uniform, const glm::vec<3, GLuint> &value) const;
        void SetVector3u(GLuint uniform, size_t count, glm::vec<3, GLuint> *values) const;
        void SetVector3u(GLuint uniform, size_t count, GLuint *values) const;

        void SetVector4f(GLuint uniform, GLfloat w, GLfloat x, GLfloat y, GLfloat z) const;
        void SetVector4f(GLuint uniform, const glm::vec<4, GLfloat> &value) const;
        void SetVector4f(GLuint uniform, size_t count, glm::vec<4, GLfloat> *values) const;
        void SetVector4f(GLuint uniform, size_t count, GLfloat *values) const;
        void SetVector4i(GLuint uniform, GLint w, GLint x, GLint y, GLint z) const;
        void SetVector4i(GLuint uniform, const glm::vec<4, GLint> &value) const;
        void SetVector4i(GLuint uniform, size_t count, glm::vec<4, GLint> *values) const;
        void SetVector4i(GLuint uniform, size_t count, GLint *values) const;
        void SetVector4u(GLuint uniform, GLuint w, GLuint x, GLuint y, GLuint z) const;
        void SetVector4u(GLuint uniform, const glm::vec<4, GLuint> &value) const;
        void SetVector4u(GLuint uniform, size_t count, glm::vec<4, GLuint> *values) const;
        void SetVector4u(GLuint uniform, size_t count, GLuint *values) const;

        void SetMatrix4(GLuint uniform, const glm::mat4 &matrix) const;
        void SetMatrix4(GLuint uniform, size_t count, glm::mat4 *values) const;
        void SetMatrix4(GLuint uniform, size_t count, GLfloat *values) const;

        GLuint GetUniform(const std::string &name, bool save = true);

    private:
        GLuint id;
        std::unordered_map<std::string, GLuint> uniforms;
    };

    Shader *CreateShaderFromFile(Container *const container, const std::string &name, const std::string &vertexLocation, const std::string &fragmentLocation);
    Shader *CreateShaderFromFile(Container *const container, const std::string &name, const std::string &vertexLocation, const std::string &geometryLocation, const std::string &fragmentLocation);
    Shader *CreateShaderFromFile(Container *const container, const std::string &name, const std::string &vertexLocation, const std::string &tesselationControlLocation, const std::string &tesselationEvaluationLocation, const std::string &fragmentLocation);
    Shader *CreateShaderFromFile(Container *const container, const std::string &name, const std::string &vertexLocation, const std::string &tesselationControlLocation, const std::string &tesselationEvaluationLocation, const std::string &geometryLocation, const std::string &fragmentLocation);
    Shader *CreateShaderFromFile(Container *const container, const std::string &name, std::shared_ptr<std::string> vertexLocation, std::shared_ptr<std::string> fragmentLocation);
    Shader *CreateShaderFromFile(Container *const container, const std::string &name, std::shared_ptr<std::string> vertexLocation, std::shared_ptr<std::string> geometryLocation, std::shared_ptr<std::string> fragmentLocation);
    Shader *CreateShaderFromFile(Container *const container, const std::string &name, std::shared_ptr<std::string> vertexLocation, std::shared_ptr<std::string> tesselationControlLocation, std::shared_ptr<std::string> tesselationEvaluationLocation, std::shared_ptr<std::string> fragmentLocation);
    Shader *CreateShaderFromFile(Container *const container, const std::string &name, std::shared_ptr<std::string> vertexLocation, std::shared_ptr<std::string> tesselationControlLocation, std::shared_ptr<std::string>  tesselationEvaluationLocation, std::shared_ptr<std::string>  geometryLocation, std::shared_ptr<std::string> fragmentLocation);
}
