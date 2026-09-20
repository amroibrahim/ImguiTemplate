#include "PropertiesPanel.hpp"


PropertiesPanel::PropertiesPanel(const char* name, ImGuiKeyChord toggleShortcut) : Panel(name, toggleShortcut)
{

}

void PropertiesPanel::OnDraw()
{
    ImGui::InputText("Name", m_name, sizeof(m_name));
    ImGui::DragFloat3("Position", m_position, 0.1f);
    ImGui::DragFloat ("Scale",   &m_scale, 0.05f, 0.0f, 100.0f);
    ImGui::ColorEdit4("Color",    m_color);
    ImGui::Checkbox  ("Visible", &m_visible);
}
