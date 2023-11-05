#pragma once

#include <GL/glew.h>
#include "Engine/Essentials/Scripts/ScriptsHeader.h"

namespace Engine::Scripts
{
    const size_t PlayerController::priority = 10;
    const size_t CameraScript::priority = 20;
    const size_t RenderScript::priority = 30;
    const size_t LightSourceScript::priority = 40;
}
