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

namespace Newtonic
{
  class Image
  {
  public:
    Image();
    ~Image();
    Image(Image && other);
    Image & operator =(Image && other);

    int GetWidth() const;
    int GetHeight() const;
    int GetBPP() const;

    unsigned char * GetBuffer() const;

    bool IsValid() const { return m_data != nullptr; }

    static Image LoadPNG(const char * path);

  private:
    unsigned char * m_data;
    int m_width;
    int m_height;
    int m_bitsPerPixel;
  };
}
