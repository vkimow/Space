#pragma once

#include <string>
#include <memory>

namespace Engine::Tools::Other
{
    std::string GetExecutableDirectory();
    std::string ReadFile(const std::string_view file_path);
    std::string ReadRelativeFile(const std::string_view file_relative_path);
}
