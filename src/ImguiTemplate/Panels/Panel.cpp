#include "Panel.hpp"


Panel::Panel(const char* name, ImGuiKeyChord toggleShortcut /*= 0*/)
  : m_szName(name), m_toggleShortcut(toggleShortcut)
{
}

void Panel::OnImGui()
{
  if (m_toggleShortcut != 0 && ImGui::Shortcut(m_toggleShortcut, ImGuiInputFlags_RouteGlobal))
  {
    m_bVisible = !m_bVisible;
  }

  if (!m_bVisible)
    return;

  if (ImGui::Begin(m_szName, &m_bVisible))
  {
    OnDraw();
  }
  ImGui::End();
}

bool Panel::IsVisible() const
{
  return m_bVisible;
}

void Panel::SetVisible(bool bVisible)
{
  m_bVisible = bVisible;
}

const char* Panel::GetName() const
{
  return m_szName;
}