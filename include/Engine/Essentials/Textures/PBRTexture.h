#pragma once
#include "Engine/Graphics/Elements/Interfaces/ITexture.h"


namespace Engine::Graphics
{
    class PBRTexture: public ITexture
    {
        friend class Container;

    private:
        PBRTexture();
        PBRTexture(const PBRTexture &rhs) = delete;
        PBRTexture(PBRTexture &&rhs) = delete;
        PBRTexture &operator=(const PBRTexture &rhs) = delete;
        PBRTexture &operator=(PBRTexture &&rhs) = delete;
        ~PBRTexture();

    public:
        void Use(Shader *shader) override final;
    };
}