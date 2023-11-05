#pragma once 
#include <glm/glm.hpp>
#include "Engine/Graphics/Light/ILight.h"
#include "Engine/Graphics/Light/LightValue.h"
#include <string>
#include <unordered_map>

namespace Engine::Graphics
{
    class AmbientLight final : public ILight
    {
        friend class LightManager;
        friend class LightContainer;

    protected:
        struct AmbientLightUniform final
        {
            AmbientLightUniform();
            AmbientLightUniform(Shader *shader, const std::string &path);
            const LightValueUniform light;
        };

    private:
        AmbientLight();
        AmbientLight(const AmbientLight &rhs) = delete;
        AmbientLight(AmbientLight &&rhs) noexcept = delete;
        AmbientLight &operator=(const AmbientLight &rhs) = delete;
        AmbientLight &operator=(AmbientLight &&rhs) noexcept = delete;
        ~AmbientLight();

    public:
        void Use(Shader *shader) override final;
        void Disable(Shader *shader) override final;

    public:
        void SetActive(bool value) override final;
        bool IsActive() const override final;

    public:
        const LightValue &GetLight() const;
        LightValue &GetLight();

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
        LightValue light;
        std::unordered_map<Shader *, AmbientLightUniform> uniforms;
    };
}
