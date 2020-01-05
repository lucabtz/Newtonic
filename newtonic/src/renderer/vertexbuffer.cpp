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

#include "vertexbuffer.h"
#include "../core.h"
#include "../util.h"

namespace Newtonic
{
  VertexBuffer::VertexBuffer() : m_vboId(INVALID_VBO_ID) {}

  VertexBuffer::VertexBuffer(const void * data, GLuint size)
  {
    NW_WRAP_GL_CALL(glGenBuffers(1, &m_vboId));
    NW_WRAP_GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_vboId));
    NW_WRAP_GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    NW_WRAP_DEBUG(Core::GetCoreLogger().Debug(FormatString("Created vertex buffer %i", m_vboId)));
  }

  VertexBuffer::VertexBuffer(VertexBuffer && other) : m_vboId(other.m_vboId) { other.m_vboId = INVALID_VBO_ID; }

  VertexBuffer::~VertexBuffer() { Clear(); }

  VertexBuffer & VertexBuffer::operator =(VertexBuffer && other)
  {
    Clear();
    m_vboId = other.m_vboId;
    other.m_vboId = INVALID_VBO_ID;
    return *this;
  }

  void VertexBuffer::Bind()   const { NW_WRAP_GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_vboId)); }
  void VertexBuffer::Unbind() const { NW_WRAP_GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, INVALID_VBO_ID)); }

  void VertexBuffer::Clear()
  {
    if (m_vboId != INVALID_VBO_ID)
    {
        NW_WRAP_GL_CALL(glDeleteBuffers(1, &m_vboId));
        m_vboId = INVALID_VBO_ID;
    }
  }
}
