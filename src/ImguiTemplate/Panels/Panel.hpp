#pragma once
#include "imgui.h"

class Panel
{
public:
  Panel(const char* name, ImGuiKeyChord toggleShortcut = 0);

  virtual ~Panel() = default;

  void OnImGui();
  bool IsVisible() const;
  void SetVisible(bool bVisible);
  const char* GetName() const;

protected:
  virtual void OnDraw() = 0;

private:
  const char* m_szName;
  ImGuiKeyChord m_toggleShortcut;
  bool m_bVisible = true;
};
