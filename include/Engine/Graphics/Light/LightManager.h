#pragma once 

#include "Engine/Graphics/Light/LightContainer.h"
#include "Engine/Graphics/Light/LightSourceUniformGetter.h"
#include "Engine/Graphics/Elements/Shader.h"
#include <unordered_set>

namespace Engine
{
    class GraphicsModule;
}

namespace Engine::Graphics
{
    class LightManager final
    {
        friend class GraphicsModule;
        friend class LightSource;

    private:
        LightManager();
        LightManager(const LightManager &rhs) = delete;
        LightManager(LightManager &&rhs) noexcept = delete;
        LightManager &operator=(const LightManager &rhs) = delete;
        LightManager &operator=(LightManager &&rhs) noexcept = delete;
        ~LightManager();

    public:
        void Use(Shader *shader);
        
    private:
        void InitializeAmbientLightsUniforms(Shader *shader);
        void InitializeDirectionalLightsUniforms(Shader *shader);
        void InitializeLightSourcesUniforms(Shader *shader);

    public:
        const LightContainer &GetContainer() const;
        LightContainer &GetContainer();

    private:
        void InitializeAmbientLightUniformsForShadersInUse(AmbientLight* light);
        void InitializeDirectionalLightUniformsForShadersInUse(DirectionalLight *light);

    private:
        Tools::Events::MemberFunction<LightManager, AmbientLight *> initializeAmbientLightUniforms;
        Tools::Events::MemberFunction<LightManager, DirectionalLight *> initializeDirectionalLightUniforms;

    private:
        LightContainer container;
        std::unordered_set<Shader *> shadersInUse;
        std::unordered_map<Shader *, LightSourceUnfiromGetter> shadersToLightSourceUniformGetter;
    };
}
