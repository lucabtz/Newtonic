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

#include "renderer/vertexbufferlayout.h"

namespace Newtonic
{
  template<>
  void VertexBufferLayout::Add<GLfloat>(unsigned int count)
  {
    m_elements.push_back({ GL_FLOAT, count, GL_FALSE, sizeof(GLfloat) });
    m_stride += sizeof(GLfloat) * count;
  }

  template<>
  void VertexBufferLayout::Add<GLuint>(unsigned int count)
  {
    m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE, sizeof(GLuint) });
    m_stride += sizeof(GLuint) * count;
  }
}
