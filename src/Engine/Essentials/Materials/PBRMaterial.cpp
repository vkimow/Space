#include "Engine/Essentials/Materials/PBRMaterial.h"

namespace Engine::Graphics
{
    PBRMaterial::PBRMaterial()
        : albedo(0.0f)
        , metallic(0.0f)
        , roughness(0.0f)
    {}

    PBRMaterial::PBRMaterial(float r, float g, float b, float a, float metallic, float roughness)
        : albedo(r, g, b, a)
        , metallic(metallic)
        , roughness(roughness)
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
        shader->SetVector4f("material.albedo", albedo);
        shader->SetFloat("material.metallic", metallic);
        shader->SetFloat("material.roughness", roughness);
    }

    void PBRMaterial::Disable(Shader *shader)
    {
        shader->SetVector4f("material.albedo", 0.0f, 0.0f, 0.0f, 0.0f);
        shader->SetFloat("material.metallic", 0.0f);
        shader->SetFloat("material.roughness", 0.0f);
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