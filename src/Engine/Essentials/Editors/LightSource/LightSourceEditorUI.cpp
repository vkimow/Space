#include "Engine/Essentials/Editors/LightSource/LightSourceEditor.h"
#include "Engine/Essentials/Editors/LightSource/LightSourceEditorUI.h"
#include "Engine/Tools/Other/ImGui.h"
#include <imgui.h>


namespace Engine::UI
{
    LightSourceEditorUI::LightSourceEditorUI(LightSourceEditor *const editor)
        : EditorUI(editor)
    {}

    LightSourceEditorUI::~LightSourceEditorUI()
    {}

    void LightSourceEditorUI::UpdateInner()
    {
        LightSourceEditor *editor = GetEditor<LightSourceEditor>();
        ImGui::Combo(GetVariableName("Type").c_str(), reinterpret_cast<int *>(editor->GetType().GetBufferPtr()), "Point Light\0Spot Light\0");
        if (editor->GetType() == Graphics::LightSourceType::SpotLight)
        {
            ImGui::SliderAngle(GetVariableName("Angle").c_str(), editor->GetAngle().GetBufferPtr(), 1.0f, 360.0f);
        }
        ImGui::LightValue("Ambient", editor->GetAmbient().GetBuffer());
        ImGui::LightValue("Diffuse", editor->GetDiffuse().GetBuffer());
        ImGui::LightValue("Specular", editor->GetSpecular().GetBuffer());
        ImGui::LightAttenuation("Attenuation", GetEditorName().c_str(), editor->GetAttenuation().GetBuffer());
        ImGui::DragFloat(GetVariableName("StartRadius").c_str(), editor->GetRadius().GetBufferPtr(), 0.1f, 0.0, 100000.0f);
    }
}