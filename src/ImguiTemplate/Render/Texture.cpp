#include "Texture.h"

Texture::Texture(SDL_Texture* handle, int width, int height)
  : m_handle(handle), m_width(width), m_height(height)
{
}

bool Texture::Valid() const
{
  return m_handle != nullptr;
}

int Texture::Width() const
{
  return m_width;
}

int Texture::Height() const
{
  return m_height;
}

Texture::~Texture()
{
  if (m_handle) 
    SDL_DestroyTexture(m_handle);
}

Texture::Texture(Texture&& other) noexcept
  : m_handle(other.m_handle), m_width(other.m_width), m_height(other.m_height)
{
  other.m_handle = nullptr;
  other.m_width = 0;
  other.m_height = 0;
}

Texture& Texture::operator=(Texture&& other) noexcept
{
  if (this != &other)
  {
    if (m_handle) 
      SDL_DestroyTexture(m_handle);

    m_handle = other.m_handle;
    m_width = other.m_width;
    m_height = other.m_height;
    other.m_handle = nullptr;
    other.m_width = 0;
    other.m_height = 0;
  }
  return *this;
}

SDL_Texture* Texture::GetHandle() const
{
  return m_handle;
}

bool Texture::Lock(void** outPixels, int* outPitch)
{
  return SDL_LockTexture(m_handle, nullptr, outPixels, outPitch);
}

void Texture::Unlock() 
{ 
  SDL_UnlockTexture(m_handle); 
}