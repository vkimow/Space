#include "Engine/Tools/Other/ImGui.h"
#include "Engine/Graphics/Light/LightAttenuation.h"
#include "Engine/Graphics/Light/LightValue.h"
#include <glm/gtc/type_ptr.hpp>

namespace ImGui
{
    void InitializeStyle()
    {
        ImGuiStyle &style = ImGui::GetStyle();
        style.Alpha = 1.0;
        style.ChildRounding = 3;
        style.WindowRounding = 3;
        style.GrabRounding = 1;
        style.GrabMinSize = 20;
        style.FrameRounding = 3;

        style.Colors[ImGuiCol_Text] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
        style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.00f, 0.40f, 0.41f, 1.00f);
        style.Colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 1.00f, 1.00f, 0.65f);
        style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        style.Colors[ImGuiCol_FrameBg] = ImVec4(0.44f, 0.80f, 0.80f, 0.18f);
        style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.44f, 0.80f, 0.80f, 0.27f);
        style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.44f, 0.81f, 0.86f, 0.66f);
        style.Colors[ImGuiCol_TitleBg] = ImVec4(0.14f, 0.18f, 0.21f, 0.73f);
        style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.54f);
        style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 1.00f, 1.00f, 0.27f);
        style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.20f);
        style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.22f, 0.29f, 0.30f, 0.71f);
        style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.00f, 1.00f, 1.00f, 0.44f);
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.00f, 1.00f, 1.00f, 0.74f);
        style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
        style.Colors[ImGuiCol_CheckMark] = ImVec4(0.00f, 1.00f, 1.00f, 0.68f);
        style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 1.00f, 1.00f, 0.36f);
        style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.00f, 1.00f, 1.00f, 0.76f);
        style.Colors[ImGuiCol_Button] = ImVec4(0.00f, 0.65f, 0.65f, 0.46f);
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.01f, 1.00f, 1.00f, 0.43f);
        style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.00f, 1.00f, 1.00f, 0.62f);
        style.Colors[ImGuiCol_Header] = ImVec4(0.00f, 1.00f, 1.00f, 0.33f);
        style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 1.00f, 1.00f, 0.42f);
        style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.00f, 1.00f, 1.00f, 0.54f);
        style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 1.00f, 1.00f, 0.54f);
        style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.00f, 1.00f, 1.00f, 0.74f);
        style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
        style.Colors[ImGuiCol_PlotLines] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
        style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
        style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
        style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
        style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 1.00f, 1.00f, 0.22f);
    }

    bool DragVector3(const char *label, glm::vec3 &vector, const char *format, ImGuiInputTextFlags flags)
    {
        return ImGui::DragFloat3(label, glm::value_ptr(vector), 0.1f, 0.0f, 0.0f, format, flags);
    }

    bool InputVector3(const char *label, glm::vec3 &vector, const char *format, ImGuiInputTextFlags flags)
    {
        return ImGui::InputFloat3(label, glm::value_ptr(vector), format, flags);
    }

    bool ColorPickerVector3(const char *label, glm::vec3 &vector, ImGuiInputTextFlags flags)
    {
        return ImGui::ColorPicker3(label, glm::value_ptr(vector), flags);
    }

    bool ColorEditVector3(const char *label, glm::vec3 &vector, ImGuiInputTextFlags flags)
    {
        return ImGui::ColorEdit3(label, glm::value_ptr(vector), flags);
    }

    void LightAttenuation(const char *label, const char *invisibleLabel, Engine::Graphics::LightAttenuation& attenuation, const char *format, ImGuiInputTextFlags flags)
    {
        Text(label);
        std::string quadraticLabel = GetLabel("Quadratic", label, invisibleLabel);
        DragFloat(quadraticLabel.c_str(), &attenuation.GetQuadratic(), 0.0f, 0.0f, 1.0f, format, flags);
        std::string linearLabel = GetLabel("Linear", label, invisibleLabel);
        DragFloat(linearLabel.c_str(), &attenuation.GetLinear(), 0.0f, 0.0f, 1.0f, format, flags);
        std::string constantLabel = GetLabel("Constant", label, invisibleLabel);
        DragFloat(constantLabel.c_str(), &attenuation.GetConstant(), 0.0001f, 0.0f, 1.0f, format, flags);
    }

    void LightValue(const char *individualLabel, Engine::Graphics::LightValue& value, const char *format, ImGuiInputTextFlags flags)
    {
        LightValue(individualLabel, individualLabel, value, format, flags);
    }

    void LightValue(const char *label, const char *invisibleLabel, Engine::Graphics::LightValue &value, const char *format, ImGuiInputTextFlags flags)
    {
        ImGui::Text(label);
        std::string colorLabel = GetLabel("Color", invisibleLabel);
        ColorEditVector3(colorLabel.c_str(), value.GetColor(), flags);
        std::string intensityLabel = GetLabel("Intensity", invisibleLabel);
        DragFloat(intensityLabel.c_str(), &value.GetIntensity(), 0.01f, 0.0f, 100.0f, format, flags);
    }
}