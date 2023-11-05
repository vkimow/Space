#include "Engine/Essentials/Materials/PBRMaterial.h"

namespace Engine::Graphics
{
    PBRMaterial::PBRMaterial()
        : albedo(0.0f)
        , metallic(0.0f)
        , roughness(0.0f)
    {}

    PBRMaterial::PBRMaterial(const glm::vec4 &albedo, float metallic, float roughness)
        : albedo(albedo)
        , metallic(metallic)
        , roughness(roughness)
    {}

    PBRMaterial::PBRMaterial(glm::vec4 &&albedo, float metallic, float roughness)
        : albedo(std::move(albedo))
        , metallic(metallic)
        , roughness(roughness)
    {}

    PBRMaterial::~PBRMaterial()
    {}

    void PBRMaterial::Use(Shader * shader)
    {
        shader->SetVector4f("albedo", albedo);
        shader->SetFloat("metallic", metallic);
        shader->SetFloat("roughness", roughness);
    }

    void PBRMaterial::SetAlbedo(const glm::vec4 &value)
    {
        albedo = value;
    }

    void PBRMaterial::SetAlbedo(glm::vec4 &&value)
    {
        albedo = std::move(value);
    }

    void PBRMaterial::SetMetallic(float value)
    {
        metallic = value;
    }

    void PBRMaterial::SetRoughness(float value)
    {
        roughness = value;
    }

    const glm::vec4 &PBRMaterial::GetAlbedo() const
    {
        return albedo;
    }

    float PBRMaterial::GetMetallic() const
    {
        return metallic;
    }

    float PBRMaterial::GetRoughness() const
    {
        return roughness;
    }
}