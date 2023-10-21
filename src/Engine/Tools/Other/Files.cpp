#include "Engine/Tools/Other/Files.h"
#include <Windows.h>
#include <fstream>
#include <errno.h>

namespace Engine::Tools::Other
{
    std::string GetExecutableDirectory()
    {
        char buffer[MAX_PATH];
        GetModuleFileNameA(NULL, buffer, MAX_PATH);
        std::string::size_type pos = std::string(buffer).find_last_of("\\/");

        return std::string(buffer).substr(0, pos);
    }

    std::string ReadFile(const std::string_view file_path) {
        std::ifstream in(file_path.data(), std::ios::in | std::ios::binary);
        if (in) {
            std::string contents;
            in.seekg(0, std::ios::end);
            contents.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&contents[0], contents.size());
            in.close();
            return std::move(contents);
        }
        throw(errno);
    }

    std::string ReadRelativeFile(const std::string_view file_relative_path) {
        return std::move(ReadFile(GetExecutableDirectory() + '/' + file_relative_path.data()));
    }
}
