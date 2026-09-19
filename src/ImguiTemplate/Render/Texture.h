#pragma once

#include <SDL3/SDL.h>

class Texture
{
public:
  Texture() = default;
  Texture(SDL_Texture* handle, int width, int height);
  ~Texture();

  Texture(const Texture&) = delete;
  Texture& operator=(const Texture&) = delete;
  Texture(Texture&& other) noexcept;
  Texture& operator=(Texture&& other) noexcept;

  bool Valid() const;
  int  Width()  const;
  int  Height() const;

  SDL_Texture* GetHandle() const;

  bool Lock(void** outPixels, int* outPitch);
  void Unlock();

private:
  SDL_Texture* m_handle;
  int m_width;
  int m_height;
};