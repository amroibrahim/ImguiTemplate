#include "LeftPanel.h"


LeftPanel::LeftPanel(const char* name, ImGuiKeyChord toggleShortcut) : Panel(name, toggleShortcut)
{
}

void LeftPanel::OnDraw()
{
    ImGui::TextUnformatted("Left panel (Ctrl+Alt+Left to toggle)");
}
