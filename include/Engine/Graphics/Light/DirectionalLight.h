#pragma once 
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Engine/Graphics/Light/ILight.h"
#include "Engine/Graphics/Light/LightValue.h"
#include <unordered_map>

namespace Engine::Graphics
{
    class DirectionalLight final: public ILight
    {
        friend class LightManager;
        friend class LightContainer;

    protected:
        struct DirectionalLightUniform final
        {
            DirectionalLightUniform();
            DirectionalLightUniform(Shader *shader, const std::string &path);      
            LightValueUniform diffuse;
            LightValueUniform specular;
            GLuint direction;
        };

    private:
        DirectionalLight();
        DirectionalLight(const DirectionalLight &rhs) = delete;
        DirectionalLight(DirectionalLight &&rhs) noexcept = delete;
        DirectionalLight &operator=(const DirectionalLight &rhs) = delete;
        DirectionalLight &operator=(DirectionalLight &&rhs) noexcept = delete;
        ~DirectionalLight();

    public:
        void Use(Shader *shader) override final;
        void Disable(Shader *shader) override final;

    public:
        void SetActive(bool value) override final;
        bool IsActive() const override final;

    public:
        void SetDirection(const glm::vec3 &value);
        void SetDirection(glm::vec3 &&value);
        void SetDirection(float x, float y, float z);

    public:
        const LightValue &GetDiffuse() const;
        const LightValue &GetSpecular() const;
        LightValue &GetDiffuse();
        LightValue &GetSpecular();
        const glm::vec3 &GetDirection() const;

    public:
        void InitializeUniform(Shader *shader, const std::string &path);
        void InitializeUniforms(auto begin, auto end, const std::string &path)
        {
            for (auto it = begin; it != end; ++it)
            {
                InitializeUniform(*it, path);
            }
        }

    private:
        bool isActive;
        LightValue diffuse;
        LightValue specular;
        glm::vec3 direction;
        std::unordered_map<Shader *, DirectionalLightUniform> uniforms;
    };
}
