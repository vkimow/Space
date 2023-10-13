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
    public:
        Shader();
        Shader(const Shader &rhs) = default;
        Shader(Shader &&rhs) = default;
        Shader& operator=(const Shader &rhs) = default;
        Shader &operator=(Shader &&rhs) = default;
        ~Shader();


    public:
        void CreateFromFiles(const std::string_view vertexLocation, const std::string_view fragmentLocation);
        void Create(const std::string_view vertexCode, const std::string_view fragmentCode);
        void Validate();
        void Use();
        void Clear();


    private:
        GLuint AddShader(GLuint theProgram, const std::string_view shaderCode, GLenum shaderType);
        void LinkProgram();

    private:
        GLuint id;
    };
}
