#pragma once
#include "Panel.h"

class LeftPanel : public Panel
{
public:
  LeftPanel(const char* name, ImGuiKeyChord toggleShortcut);

protected:
    void OnDraw() override;
};
