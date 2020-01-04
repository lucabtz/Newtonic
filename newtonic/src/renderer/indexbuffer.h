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

#define INVALID_INDEX_BUFFER_ID 0

namespace Newtonic
{
  class IndexBuffer
  {
  public:
    IndexBuffer();
    IndexBuffer(const GLuint * data, unsigned int indicesCount);
    IndexBuffer(IndexBuffer && other);
    ~IndexBuffer();

    IndexBuffer & operator =(IndexBuffer && other);

    void Bind() const;
    void Unbind() const;

    unsigned int GetIndicesCount() const { return m_indicesCount; }
  private:
    GLuint m_bufferId;
    unsigned int m_indicesCount;
  };
}
