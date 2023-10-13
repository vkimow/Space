#pragma once

#include "Scene.h"

namespace Game
{
    class Scene_1 final: public Scene
    {
    public:
        Scene_1(const std::string &name, Engine::Modules *const modules);
        ~Scene_1();

    public:
        virtual void Update() override;
        virtual void Render() override;

    private:
        Engine::Input::PressableKey *f;
        Engine::Input::PressableMouse *leftButton;
        Engine::Input::DeltaPressable *delta;

        Engine::Input::VectorPressable *vector;
        Engine::Input::Mouse *mouse;

        Engine::Graphics::Shader shader;
        GLuint VertexArrayObject;
    };
}