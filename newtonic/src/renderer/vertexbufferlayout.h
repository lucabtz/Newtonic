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

#include <vector>
#include "opengl.h"

#include "../util.h"
#include "../core.h"

namespace Newtonic
{
  struct BufferElement
  {
    unsigned int m_type;
    unsigned int m_count;
    GLenum m_normalized;
    unsigned int m_size;
  };

  class VertexBufferLayout
  {
  public:
    template<typename T>
    void Add(unsigned int count);

    const std::vector<BufferElement> & GetElements() const { return m_elements; }
    unsigned int GetStride() const { return m_stride; }

  private:
    std::vector<BufferElement> m_elements;
    unsigned int m_stride = 0;
  };

  template<>
  void VertexBufferLayout::Add<GLfloat>(unsigned int count);

  template<>
  void VertexBufferLayout::Add<GLuint>(unsigned int count);
}
