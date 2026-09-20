#include "ConsolePanel.hpp"


ConsolePanel::ConsolePanel(const char* name, ImGuiKeyChord toggleShortcut) : Panel(name, toggleShortcut)
{
}

void ConsolePanel::Log(const char* line)
{
    m_lines.emplace_back(line);
}

void ConsolePanel::Clear()
{
  m_lines.clear();
}

void ConsolePanel::OnDraw()
{
    if (ImGui::SmallButton("Clear")) Clear();
    ImGui::SameLine();
    ImGui::Checkbox("Auto-scroll", &m_autoScroll);
    ImGui::Separator();

    if (ImGui::BeginChild("ConsoleScroll", ImVec2(0, 0), false,
                          ImGuiWindowFlags_HorizontalScrollbar))
    {
        for (const auto& line : m_lines)
            ImGui::TextUnformatted(line.c_str());

        if (m_autoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
            ImGui::SetScrollHereY(1.0f);
    }
    ImGui::EndChild();
}
