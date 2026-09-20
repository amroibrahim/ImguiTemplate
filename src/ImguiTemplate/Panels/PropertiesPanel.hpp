#pragma once
#include "Panel.hpp"

class PropertiesPanel : public Panel
{
public:
  PropertiesPanel(const char* name, ImGuiKeyChord toggleShortcut);

protected:
    void OnDraw() override;

private:
    char  m_name[64]   = "Untitled";
    float m_position[3]= { 0.0f, 0.0f, 0.0f };
    float m_scale      = 1.0f;
    float m_color[4]   = { 1.0f, 1.0f, 1.0f, 1.0f };
    bool  m_visible    = true;
};
