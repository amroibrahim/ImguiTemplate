#pragma once
#include "SdlContext.hpp"
#include "Panel.hpp"
#include <memory>
#include <string>
#include <vector>

class ViewportPanel;

class Application
{
public:
  Application();
  bool Init(std::string sAppName);
  void Run();
  void Shutdown();

private:
  void BuildDefaultDockLayoutIfNeeded(unsigned int dockspaceId);

  std::vector<std::unique_ptr<Panel>> m_panels;

  SdlContext  m_sdl;
  ViewportPanel* m_viewport;
  bool  m_fullscreenViewport;
  bool m_layoutChecked;
};
