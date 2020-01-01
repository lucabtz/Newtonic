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

#include "image.h"

#include "stb_image.h"

#include "core.h"
#include "util.h"

namespace Newtonic
{
  Image::Image() : m_data(nullptr), m_width(0), m_height(0), m_bitsPerPixel(0) {}
  Image::~Image() { if (m_data) stbi_image_free(m_data); }

  Image::Image(Image && other) : m_data(other.m_data), m_width(other.m_width), m_height(other.m_height), m_bitsPerPixel(other.m_bitsPerPixel)
  {
    other.m_data = nullptr;
  }

  Image & Image::operator =(Image && other)
  {
    if (m_data) stbi_image_free(m_data);
    m_data = other.m_data;
    other.m_data = nullptr;
    m_width = other.m_width;
    m_height = other.m_height;
    m_bitsPerPixel = other.m_bitsPerPixel;
    return *this;
  }

  int Image::GetWidth()  const { return m_width; }
  int Image::GetHeight() const { return m_height; }
  int Image::GetBPP()    const { return m_bitsPerPixel; }

  unsigned char * Image::GetBuffer() const { return m_data; }

  Image Image::LoadPNG(const char * path)
  {
    Image result;
    stbi_set_flip_vertically_on_load(1);
    result.m_data = stbi_load(path, &result.m_width, &result.m_height, &result.m_bitsPerPixel, 4);
    if (result.m_data == nullptr)
    {
      Core::GetCoreLogger().Error(FormatString("Cannot load image from %s", path));
    }
    else
    {
      NW_WRAP_DEBUG(Core::GetCoreLogger().Debug(FormatString("Loaded image from %s, width %i height %i bpp %i at %p", path, result.m_width, result.m_height, result.m_bitsPerPixel, result.m_data)));
    }
    return result;
  }
}
