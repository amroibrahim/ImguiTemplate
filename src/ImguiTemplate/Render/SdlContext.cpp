#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>

#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"

#include "SdlContext.hpp"

SdlContext::~SdlContext() 
{ 
  Shutdown();
}

bool SdlContext::Init(const char* title, int width, int height)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return false;
    }

    m_window = SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN);

    if (!m_window) 
    { 
      SDL_Log("CreateWindow: %s", SDL_GetError()); 
      return false; 
    }

    m_renderer = SDL_CreateRenderer(m_window, nullptr);
    if (!m_renderer) 
    {
      SDL_Log("CreateRenderer: %s", SDL_GetError());
      return false;
    }

    SDL_SetRenderVSync(m_renderer, 1);
    SDL_ShowWindow(m_window);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::StyleColorsDark();

    if (!ImGui_ImplSDL3_InitForSDLRenderer(m_window, m_renderer)) 
      return false;

    if (!ImGui_ImplSDLRenderer3_Init(m_renderer))
    {
      return false;
    }

    m_imguiInitialized = true;

    return true;
}

void SdlContext::Shutdown()
{
    if (m_imguiInitialized)
    {
        ImGui_ImplSDLRenderer3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
        m_imguiInitialized = false;
    }

    if (m_renderer) 
    { 
      SDL_DestroyRenderer(m_renderer); 
      m_renderer = nullptr; 
    }

    if (m_window)   
    { 
      SDL_DestroyWindow(m_window);
      m_window   = nullptr; 
    }

    SDL_Quit();
}

bool SdlContext::PumpEvents()
{
    SDL_Event ev;
    bool keepRunning = true;
    while (SDL_PollEvent(&ev))
    {
        ImGui_ImplSDL3_ProcessEvent(&ev);
        if (ev.type == SDL_EVENT_QUIT) keepRunning = false;
        if (ev.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED &&
            ev.window.windowID == SDL_GetWindowID(m_window)) keepRunning = false;
    }
    return keepRunning;
}

void SdlContext::NewFrame()
{
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}

void SdlContext::Render(Texture* fullscreenTexture)
{
    ImGui::Render();
    SDL_SetRenderDrawColorFloat(m_renderer, 0.1f, 0.1f, 0.1f, 1.0f);
    SDL_RenderClear(m_renderer);

    if (fullscreenTexture && fullscreenTexture->Valid())
    {
        SDL_RenderTexture(
            m_renderer,
            (SDL_Texture*)fullscreenTexture->GetHandle(),
            nullptr, nullptr);
    }

    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), m_renderer);
    SDL_RenderPresent(m_renderer);
}

void SdlContext::GetOutputSize(int* width, int* height) const
{
    SDL_GetRenderOutputSize(m_renderer, width, height);
}

void SdlContext::SetFullscreen(bool fullscreen)
{
    if (!m_window) 
      return;

    if (fullscreen)
    {
        SDL_SetWindowFullscreen(m_window, true);
    }
    else
    {
        SDL_SetWindowFullscreen(m_window, false);
    }
}

Texture SdlContext::CreateStreamingTexture(int width, int height)
{
    SDL_Texture* pTexture = SDL_CreateTexture(
        m_renderer,
        SDL_PIXELFORMAT_ABGR8888,
        SDL_TEXTUREACCESS_STREAMING,
        width, height);

    if (pTexture)
      SDL_SetTextureScaleMode(pTexture, SDL_SCALEMODE_NEAREST);

    return Texture(pTexture, width, height);
}
