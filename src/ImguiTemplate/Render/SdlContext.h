#pragma once
#include "Texture.h"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
union  SDL_Event;

class SdlContext
{
public:
    SdlContext() = default;
    ~SdlContext();

    SdlContext(const SdlContext&)            = delete;
    SdlContext& operator=(const SdlContext&) = delete;

    bool Init(const char* title, int width, int height);
    void Shutdown();

    bool PumpEvents();
    
    void SetFullscreen(bool fullscreen);
    void NewFrame();
    void Render(Texture* fullscreenTexture = nullptr);
    void GetOutputSize(int* width, int* height) const;

    Texture CreateStreamingTexture(int width, int height);    

private:
    SDL_Window*   m_window   = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    bool          m_imguiInitialized = false;
};
