#pragma once
#include "Panel.hpp"
#include <string>
#include <vector>

class ConsolePanel : public Panel
{
public:
  ConsolePanel(const char* name, ImGuiKeyChord toggleShortcut);

    void Log(const char* line);
    void Clear();

protected:
    void OnDraw() override;

private:
    std::vector<std::string> m_lines;
    bool m_autoScroll = true;
};
