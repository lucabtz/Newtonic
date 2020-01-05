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

#include "indexbuffer.h"
#include "../util.h"
#include "../core.h"

namespace Newtonic
{
  IndexBuffer::IndexBuffer() : m_bufferId(INVALID_INDEX_BUFFER_ID), m_indicesCount(0) {}

  IndexBuffer::IndexBuffer(const GLuint * data, unsigned int indicesCount) :
    m_indicesCount(indicesCount)
  {
    NW_WRAP_GL_CALL(glGenBuffers(1, &m_bufferId));
    NW_WRAP_GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId));
    NW_WRAP_GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesCount * sizeof(GLuint), data, GL_STATIC_DRAW));
    NW_WRAP_DEBUG(Core::GetCoreLogger().Debug(FormatString("Created index buffer %i", m_bufferId)));
  }

  IndexBuffer::IndexBuffer(IndexBuffer && other) :
    m_bufferId(other.m_bufferId),
    m_indicesCount(other.m_indicesCount)
  {
    other.m_bufferId = INVALID_INDEX_BUFFER_ID;
    other.m_indicesCount = 0;
  }

  IndexBuffer::~IndexBuffer() { Clear(); }

  IndexBuffer & IndexBuffer::operator =(IndexBuffer && other)
  {
    Clear();
    m_bufferId = other.m_bufferId;
    m_indicesCount = other.m_indicesCount;
    other.m_bufferId = INVALID_INDEX_BUFFER_ID;
    other.m_indicesCount = 0;
    return *this;
  }

  void IndexBuffer::Bind()   const { NW_WRAP_GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId)); }
  void IndexBuffer::Unbind() const { NW_WRAP_GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, INVALID_INDEX_BUFFER_ID)); }

  void IndexBuffer::Clear()
  {
    if (m_bufferId != INVALID_INDEX_BUFFER_ID)
    {
       NW_WRAP_GL_CALL(glDeleteBuffers(1, &m_bufferId));
       m_bufferId = INVALID_INDEX_BUFFER_ID;
    }
    m_indicesCount = 0;
  }
}
