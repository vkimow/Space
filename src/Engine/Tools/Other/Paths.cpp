#include "Engine/Tools/Other/Paths.h"
#include <Windows.h>

namespace Engine::Tools::Other
{
    std::string GetExecutableDirectory()
    {
        char buffer[MAX_PATH];
        GetModuleFileNameA(NULL, buffer, MAX_PATH);
        std::string::size_type pos = std::string(buffer).find_last_of("\\/");

        return std::string(buffer).substr(0, pos);
    }
}
