#include "ViewportPanel.hpp"
#include <cstring>

constexpr uint32_t CLEAR_COLOR = 0xFF202020u; // ARGB format

ViewportPanel::ViewportPanel(SdlContext& sdl, const char* name) : Panel(name), m_sdl(sdl), m_texture(), m_pixels(nullptr)
{
}

void ViewportPanel::OnDraw()
{
    ImVec2 avail = ImGui::GetContentRegionAvail();
    int width = (int)avail.x;
    int height = (int)avail.y;

    if (width <= 0 || height <= 0) 
      return;

    Update(width, height);

    ImGui::Image(m_texture.GetHandle(), ImVec2((float)width, (float)height));
}

void ViewportPanel::Update(int width, int height)
{
    if (width <= 0 || height <= 0)
      return;

    EnsureSize(width, height);

    // update m_pixels[y * width + x] 

    BlitPixelsToTexture();
}

Texture& ViewportPanel::GetTexture()
{
  return m_texture;
}

void ViewportPanel::EnsureSize(int width, int height)
{
    if (m_texture.Valid() &&
        m_texture.Width() == width &&
        m_texture.Height() == height) return;

    m_texture = m_sdl.CreateStreamingTexture(width, height);

    m_pixels = std::make_unique<uint32_t[]>((size_t)width * height);
    std::fill_n(m_pixels.get(), (size_t)width * height, CLEAR_COLOR);
}

void ViewportPanel::BlitPixelsToTexture()
{
    void* dst   = nullptr;
    int   pitch = 0;
   
    if (!m_texture.Lock(&dst, &pitch))
      return;

    const int width = m_texture.Width();
    const int height = m_texture.Height();
    for (int y = 0; y < height; ++y)
    {
        std::memcpy(
            (uint8_t*)dst + (size_t)y * pitch,
            m_pixels.get() + (size_t)y * width,
            (size_t)width * sizeof(uint32_t));
    }
    m_texture.Unlock();
}
