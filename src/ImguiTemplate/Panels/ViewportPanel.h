#pragma once

#include "Panel.h"
#include "SdlContext.h"
#include "Texture.h"

#include <vector>
#include <cstdint>
#include <memory>

class ViewportPanel : public Panel
{
public:
    ViewportPanel(SdlContext& sdl, const char* name);

    void Update(int width, int height);

    Texture& GetTexture();

protected:
    void OnDraw() override;

private:
    void EnsureSize(int width, int height);
    void BlitPixelsToTexture();

    SdlContext& m_sdl;
    Texture m_texture;
    std::unique_ptr<uint32_t[]> m_pixels;
};
