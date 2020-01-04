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

#pragma once

#include "opengl.h"

#include "../image.h"

#define INVALID_TEXTURE_ID 0
#define MAX_SLOTS 32

namespace Newtonic
{
  class Texture
  {
  public:
    Texture();
    ~Texture();
    Texture(const Image & image);
    Texture(Texture && other);
    Texture & operator =(Texture && other);

    void Bind(unsigned int slot = 0) const;
    void Unbind(unsigned int slot = 0) const;

    int GetWidth() const;
    int GetHeight() const;
    int GetBPP() const;

    GLuint GetTextureId() const;

    void LoadFromImage(const Image & image);
  private:
    GLuint m_textureId;
    int m_width;
    int m_height;
    int m_bitsPerPixel;
  };
}
