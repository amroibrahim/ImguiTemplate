#pragma once
#include "Panel.hpp"

class RightPanel : public Panel
{
public:
  RightPanel(const char* name, ImGuiKeyChord toggleShortcut);

protected:
    void OnDraw() override;
};
