#pragma once
#include "Panel.h"

class RightPanel : public Panel
{
public:
  RightPanel(const char* name, ImGuiKeyChord toggleShortcut);

protected:
    void OnDraw() override;
};
