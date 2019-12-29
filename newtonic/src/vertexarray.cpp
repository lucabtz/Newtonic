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

#include "vertexarray.h"
#include "opengl.h"

#include "core.h"
#include "util.h"

namespace Newtonic
{
  VertexArray::VertexArray()
  {
      NW_WRAP_GL_CALL(glGenVertexArrays(1, &m_vaoId));
      NW_WRAP_GL_CALL(glBindVertexArray(m_vaoId));
      NW_WRAP_DEBUG(Core::GetCoreLogger().Debug(FormatString("Created vertex array %i", m_vaoId)));
  }

  VertexArray::VertexArray(VertexArray && other) :
    m_vaoId(other.m_vaoId)
  {
    other.m_vaoId = INVALID_VAO_ID;
  }

  VertexArray::~VertexArray() { if (m_vaoId != INVALID_VAO_ID) NW_WRAP_GL_CALL(glDeleteVertexArrays(1, &m_vaoId)); }

  VertexArray & VertexArray::operator =(VertexArray && other)
  {
    if (m_vaoId != INVALID_VAO_ID) NW_WRAP_GL_CALL(glDeleteVertexArrays(1, &m_vaoId));
    m_vaoId = other.m_vaoId;
    other.m_vaoId = INVALID_VAO_ID;
  }

  void VertexArray::Bind() const { NW_WRAP_GL_CALL(glBindVertexArray(m_vaoId)); }
  void VertexArray::Unbind() const { NW_WRAP_GL_CALL(glBindVertexArray(INVALID_VAO_ID)); }

  void VertexArray::AddBuffer(const VertexBuffer & vb, const VertexBufferLayout & layout)
  {
    Bind();
    vb.Bind();
    const auto & elems = layout.GetElements();
    unsigned int offset = 0;
    unsigned int i = 0;
    for (; i < elems.size(); ++i)
    {
      const BufferElement & elem = elems[i];
      NW_WRAP_GL_CALL(glEnableVertexAttribArray(m_firstFreeAttribute + i));
      NW_WRAP_GL_CALL(glVertexAttribPointer(m_firstFreeAttribute + i, elem.m_count, elem.m_type, elem.m_normalized, layout.GetStride(), (const void*)offset));
      offset += elem.m_size * elem.m_count;
    }
    m_firstFreeAttribute += i;
  }
}
