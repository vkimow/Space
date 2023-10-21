#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

namespace Engine::Graphics
{
    class Shader
    {
        friend class Container;

    private:
        Shader() = delete;
        Shader(const std::string &vertexLocation, const std::string &fragmentLocation);
        Shader(const std::string &vertexLocation, const std::string &geometryLocation, const std::string &fragmentLocation);
        Shader(const std::string &vertexLocation, const std::string &tesselationControlLocation, const std::string &tesselationEvaluationLocation, const std::string &fragmentLocation);
        Shader(const std::string &vertexLocation, const std::string &tesselationControlLocation, const std::string &tesselationEvaluationLocation, const std::string &geometryLocation, const std::string &fragmentLocation);
        Shader(std::shared_ptr<std::string> vertexLocation, std::shared_ptr<std::string> fragmentLocation);
        Shader(std::shared_ptr<std::string> vertexLocation, std::shared_ptr<std::string> geometryLocation, std::shared_ptr<std::string> fragmentLocation);
        Shader(std::shared_ptr<std::string> vertexLocation, std::shared_ptr<std::string> tesselationControlLocation, std::shared_ptr<std::string> tesselationEvaluationLocation, std::shared_ptr<std::string> fragmentLocation);
        Shader(std::shared_ptr<std::string> vertexLocation, std::shared_ptr<std::string> tesselationControlLocation, std::shared_ptr<std::string>  tesselationEvaluationLocation, std::shared_ptr<std::string>  geometryLocation, std::shared_ptr<std::string> fragmentLocation);
        Shader(const Shader &rhs) = delete;
        Shader(Shader &&rhs) = delete;
        Shader &operator=(const Shader &rhs) = delete;
        Shader &operator=(Shader &&rhs) = delete;
        ~Shader();

    private:
        void Create(std::shared_ptr<std::string> vertexLocation, std::shared_ptr<std::string> tesselationControlLocation, std::shared_ptr<std::string> tesselationEvaluationLocation, std::shared_ptr<std::string> geometryLocation, std::shared_ptr<std::string> fragmentLocation);
        GLuint AddShader(GLuint theProgram, std::shared_ptr<std::string> shaderCode, GLenum shaderType);
        void LinkProgram();
        void GetUniforms();

    public:
        void Validate();
        void Use();
        void Clear();

        GLuint GetModelUniform() const { return uniformModel; }
        GLuint GetViewUniform() const { return uniformView; }
        GLuint GetProjectionUniform() const { return uniformProjection; }

    private:
        GLuint id;

    private:
        GLuint uniformModel, uniformView, uniformProjection;
    };
}
