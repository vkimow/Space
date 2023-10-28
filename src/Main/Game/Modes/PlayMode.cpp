#include "Game/Modes/PlayMode.h"

namespace Main::Game
{
    PlayMode::PlayMode(Engine::Objects::Scene *scene)
        : scene(scene)
    {}

    PlayMode::~PlayMode()
    {}

    void PlayMode::Start()
    {}

    void PlayMode::Update()
    {
        scene->Update();
    }

    void PlayMode::End()
    {}
}