#pragma once
#include "Engine/Graphics/Elements/Interfaces/IMaterial.h"

namespace Engine::Graphics
{
    class PBRMaterial: public IMaterial
    {
        friend class Container;

    private:
        PBRMaterial();
        PBRMaterial(float r, float g, float b, float a, float metallic = 1.0f, float roughness = 1.0f);
        PBRMaterial(const glm::vec4 &albedo, float metallic = 1.0f, float roughness = 1.0f);
        PBRMaterial(glm::vec4 &&albedo, float metallic = 1.0f, float roughness = 1.0f);
        PBRMaterial(const PBRMaterial &rhs) = delete;
        PBRMaterial(PBRMaterial &&rhs) = delete;
        PBRMaterial &operator=(const PBRMaterial &rhs) = delete;
        PBRMaterial &operator=(PBRMaterial &&rhs) = delete;
        ~PBRMaterial();

    public:
        void Use(Shader *shader) override final;
        void Disable(Shader *shader) override final;

    public:
        void SetAlbedo(const glm::vec4 &value);
        void SetAlbedo(glm::vec4 &&value);
        void SetMetallic(float value);
        void SetRoughness(float value);

    public:
        const glm::vec4 &GetAlbedo() const;
        float GetMetallic() const;
        float GetRoughness() const;

    private:
        glm::vec4 albedo;
        float metallic;
        float roughness;
    };
}