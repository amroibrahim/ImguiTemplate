#include "RightPanel.hpp"


RightPanel::RightPanel(const char* name, ImGuiKeyChord toggleShortcut) : Panel(name, toggleShortcut)
{
}

void RightPanel::OnDraw()
{
    ImGui::TextUnformatted("Right panel (Ctrl+Alt+Right to toggle)");
}
