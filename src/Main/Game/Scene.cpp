#include "Scene.h"

namespace Game
{
    size_t Scene::idCounter = 0;

    Scene::Scene(const std::string &name, Engine::Modules *const modules)
        : id(idCounter++)
        , name(name)
        , modules(modules)
    {}
}