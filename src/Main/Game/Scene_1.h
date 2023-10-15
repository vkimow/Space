#pragma once

#include "Engine/Main/EngineHeader.h"

namespace Game
{
    class Scene_1 final: public Engine::Objects::Scene
    {
    public:
        Scene_1(const std::string &name, Engine::Window *const window, Engine::Modules *const modules);
        ~Scene_1();

    public:
        virtual void Update() override;
        virtual void Render() override;

    private:
        Engine::Input::VectorPressable *movementInput;
        Engine::Input::Mouse *mouseInput;

        Engine::Graphics::Shader shader;

        Engine::Graphics::Mesh mesh_1;
        Engine::Graphics::Mesh mesh_2;
        Engine::Graphics::Mesh mesh_3;
        Engine::Graphics::Mesh mesh_4;
        Engine::Graphics::Mesh mesh_5;

        Engine::Graphics::Camera camera;
        Engine::Graphics::Projection projection;
    };
}