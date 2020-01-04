/*
 *   Newtonic
 *   Copyright (C) 2019 Luca "ekardnam" Bertozzi <luca.bertozzi11@studio.unibo.it>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "texture.h"

#include "../util.h"

namespace Newtonic
{
  Texture::Texture() : m_textureId(INVALID_TEXTURE_ID), m_width(0), m_height(0), m_bitsPerPixel(0)
  {}

  Texture::Texture(const Image & image) : Texture()
  {
    LoadFromImage(image);
  }

  Texture::Texture(Texture && other) : m_textureId(other.m_textureId), m_width(other.m_width), m_height(other.m_height), m_bitsPerPixel(other.m_bitsPerPixel)
  {
    other.m_textureId = INVALID_TEXTURE_ID;
  }

  Texture::~Texture()
  {
    if (m_textureId != INVALID_TEXTURE_ID)
    {
      NW_WRAP_GL_CALL(glDeleteTextures(1, &m_textureId));
    }
  }

  Texture & Texture::operator =(Texture && other)
  {
    if (m_textureId != INVALID_TEXTURE_ID)
    {
      NW_WRAP_GL_CALL(glDeleteTextures(1, &m_textureId));
    }

    m_textureId = other.m_textureId;
    other.m_textureId = INVALID_TEXTURE_ID;
    m_width = other.m_width;
    m_height = other.m_height;
    m_bitsPerPixel = other.m_bitsPerPixel;
    return *this;
  }

  void Texture::Bind(unsigned int slot) const
  {
    ASSERT_TRUE(slot < MAX_SLOTS);
    NW_WRAP_GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
    NW_WRAP_GL_CALL(glBindTexture(GL_TEXTURE_2D, m_textureId));
  }

  void Texture::Unbind(unsigned int slot) const
  {
    ASSERT_TRUE(slot < MAX_SLOTS);
    NW_WRAP_GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
    NW_WRAP_GL_CALL(glBindTexture(GL_TEXTURE_2D, INVALID_TEXTURE_ID));
  }

  int Texture::GetWidth()  const { return m_width; }
  int Texture::GetHeight() const { return m_height; }
  int Texture::GetBPP()    const { return m_bitsPerPixel; }
  GLuint Texture::GetTextureId() const { return m_textureId; }

  void Texture::LoadFromImage(const Image & image)
  {
    if (m_textureId != INVALID_TEXTURE_ID)
    {
       NW_WRAP_GL_CALL(glDeleteTextures(1, &m_textureId));
    }

    NW_WRAP_GL_CALL(glGenTextures(1, &m_textureId));
    Bind();

    NW_WRAP_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    NW_WRAP_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    NW_WRAP_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP));
    NW_WRAP_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP));

    m_width = image.GetWidth();
    m_height = image.GetHeight();
    m_bitsPerPixel = image.GetBPP();

    NW_WRAP_GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.GetBuffer()));

    Unbind();

    NW_WRAP_DEBUG(Core::GetCoreLogger().Debug(FormatString("Loaded texture %i", m_textureId)));
  }

}
