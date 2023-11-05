#pragma once

#include <glm/glm.hpp>
#include <imgui.h>
#include <sstream>
#include <string>

namespace Engine::Graphics
{
    class LightAttenuation;
    class LightValue;
}

namespace ImGui
{
    void InitializeStyle();

    bool DragVector3(const char *label, glm::vec3 &vector, const char *format = "%.3f", ImGuiInputTextFlags flags = 0);
    bool InputVector3(const char *label, glm::vec3 &vector, const char *format = "%.3f", ImGuiInputTextFlags flags = 0);
    bool ColorPickerVector3(const char *label, glm::vec3 &vector, ImGuiInputTextFlags flags = 0);
    bool ColorEditVector3(const char *label, glm::vec3 &vector, ImGuiInputTextFlags flags = 0);
    void LightAttenuation(const char *label, const char *invisibleLabel, Engine::Graphics::LightAttenuation& attenuation, const char *format = "%.3f", ImGuiInputTextFlags flags = 0);

    void LightValue(const char *label, Engine::Graphics::LightValue& value, const char *format = "%.3f", ImGuiInputTextFlags flags = 0);
    void LightValue(const char *label, const char* invisibleLabel, Engine::Graphics::LightValue &value, const char *format = "%.3f", ImGuiInputTextFlags flags = 0);

    template<typename T1, typename T2>
    std::string GetLabel(T1 &&label, T2 &&invisibleLabel)
    {
        std::ostringstream ss;
        ss << std::forward<T1>(label) << "##" << std::forward<T2>(invisibleLabel);
        return ss.str();
    }   

    template<typename T1, typename T2, typename T3>
    std::string GetLabel(T1 && label, T2 && invisibleLabel_1, T3 && invisibleLabel_2)
    {
        std::ostringstream ss;
        ss << std::forward<T1>(label) << "##" << std::forward<T2>(invisibleLabel_1) << std::forward<T3>(invisibleLabel_2);
        return ss.str();
    }

    template<typename T1, typename T2>
    std::string GetInvisibleLabel(T1 &&invisibleLabel_1, T2 &&invisibleLabel_2)
    {
        std::ostringstream ss;
        ss << "##" << std::forward<T1>(invisibleLabel_1) << std::forward<T2>(invisibleLabel_2);
        return ss.str();
    }

    template<typename T1, typename T2>
    std::string GetInvisibleLabelC(T1 &&invisibleLabel_1, T2 &&invisibleLabel_2)
    {
        std::ostringstream ss;
        ss << "##" << std::forward<T1>(invisibleLabel_1) << std::forward<T2>(invisibleLabel_2);
        return ss.str().c_str();
    }

    template<typename T1, typename T2>
    const char *GetLabelC(T1 &&label, T2 &&invisibleLabel)
    {
        std::ostringstream ss;
        ss << std::forward<T1>(label) << "##" << std::forward<T2>(invisibleLabel);
        return ss.str().c_str();
    }

    template<typename T1, typename T2, typename T3>
    const char *GetLabelC(T1 &&label, T2 &&invisibleLabel_1, T3 &&invisibleLabel_2)
    {
        std::ostringstream ss;
        ss << std::forward<T1>(label) << "##" << std::forward<T2>(invisibleLabel_1) << std::forward<T3>(invisibleLabel_2);
        return ss.str().c_str();
    }
}