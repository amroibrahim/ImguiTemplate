#include "Application.hpp"
#include "LeftPanel.hpp"
#include "RightPanel.hpp"
#include "ViewportPanel.hpp"
#include "ConsolePanel.hpp"
#include "PropertiesPanel.hpp"

#include "imgui.h"
#include "imgui_internal.h"

Application::Application() : m_viewport(nullptr), m_fullscreenViewport(false), m_layoutChecked(false)
{

}

bool Application::Init(std::string sAppName)
{
  if (!m_sdl.Init(sAppName.c_str(), 1280, 720))
    return false;

  std::unique_ptr<ViewportPanel> viewport = std::make_unique<ViewportPanel>(m_sdl, "Viewport");
  m_viewport = viewport.get();

  m_panels.emplace_back(std::move(viewport));
  m_panels.emplace_back(std::make_unique<LeftPanel>("Left", ImGuiMod_Ctrl | ImGuiMod_Alt | ImGuiKey_LeftArrow));
  m_panels.emplace_back(std::make_unique<RightPanel>("Right", ImGuiMod_Ctrl | ImGuiMod_Alt | ImGuiKey_RightArrow));
  m_panels.emplace_back(std::make_unique<ConsolePanel>("Console", ImGuiMod_Ctrl | ImGuiMod_Alt | ImGuiKey_DownArrow));
  m_panels.emplace_back(std::make_unique<PropertiesPanel>("Properties", ImGuiMod_Ctrl | ImGuiMod_Alt | ImGuiKey_P));
  return true;
}

void Application::Run()
{
  const ImGuiKeyChord kFullscreenChord = ImGuiMod_Ctrl | ImGuiMod_Alt | ImGuiKey_UpArrow;
  const ImGuiKeyChord kFullscreenChordAlt = ImGuiMod_Ctrl | ImGuiMod_Alt | ImGuiKey_F;

  while (m_sdl.PumpEvents())
  {
    m_sdl.NewFrame();

    if (ImGui::Shortcut(kFullscreenChord, ImGuiInputFlags_RouteGlobal) ||
      ImGui::Shortcut(kFullscreenChordAlt, ImGuiInputFlags_RouteGlobal))
    {
      m_fullscreenViewport = !m_fullscreenViewport;
    }

    if (ImGui::Shortcut(kFullscreenChordAlt, ImGuiInputFlags_RouteGlobal))
    {
      m_sdl.SetFullscreen(m_fullscreenViewport);
    }

    if (!m_fullscreenViewport)
    {
      ImGuiID dockspaceId = ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());

      BuildDefaultDockLayoutIfNeeded(dockspaceId);

      for (auto& panel : m_panels)
        panel->OnImGui();

      m_sdl.Render();
    }
    else
    {
      int width = 0, height = 0;
      m_sdl.GetOutputSize(&width, &height);
      m_viewport->Update(width, height);
      m_sdl.Render(&m_viewport->GetTexture());
    }
  }
}

void Application::Shutdown()
{
  m_sdl.Shutdown();
}

void Application::BuildDefaultDockLayoutIfNeeded(unsigned int dockspaceId)
{
  if (m_layoutChecked) return;
  m_layoutChecked = true;

  ImGuiDockNode* node = ImGui::DockBuilderGetNode(dockspaceId);

  if (node && !node->IsEmpty())
    return;


  ImGui::DockBuilderRemoveNode(dockspaceId);
  ImGui::DockBuilderAddNode(dockspaceId, ImGuiDockNodeFlags_DockSpace);
  ImGui::DockBuilderSetNodeSize(dockspaceId, ImGui::GetMainViewport()->Size);


  ImGuiID center = dockspaceId;

  ImGuiID bottom = ImGui::DockBuilderSplitNode(center, ImGuiDir_Down, 0.25f, nullptr, &center);
  ImGuiID left = ImGui::DockBuilderSplitNode(center, ImGuiDir_Left, 0.20f, nullptr, &center);
  ImGuiID right = ImGui::DockBuilderSplitNode(center, ImGuiDir_Right, 0.20f, nullptr, &center);
  ImGuiID rightBottom = ImGui::DockBuilderSplitNode(right, ImGuiDir_Down, 0.50f, nullptr, &right);

  ImGui::DockBuilderDockWindow("Left", left);
  ImGui::DockBuilderDockWindow("Right", right);
  ImGui::DockBuilderDockWindow("Properties", rightBottom);
  ImGui::DockBuilderDockWindow("Console", bottom);
  ImGui::DockBuilderDockWindow("Viewport", center);

  ImGui::DockBuilderFinish(dockspaceId);
}
