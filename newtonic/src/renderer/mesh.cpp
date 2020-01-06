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

#include "mesh.h"

#include "../core.h"
#include "../util.h"

#include "vertexbuffer.h"
#include "vertexbufferlayout.h"

#include <utility>

namespace Newtonic
{
  Mesh::Mesh()
    : m_vertices(),
      m_vertexArray(),
      m_indexBuffer(),
      m_vertexBuffer()
  {}

  Mesh::Mesh(Mesh && other)
    : m_vertices(std::move(other.m_vertices)),
      m_vertexArray(std::move(other.m_vertexArray)),
      m_indexBuffer(std::move(other.m_indexBuffer)),
      m_vertexBuffer(std::move(other.m_vertexBuffer))
  {}

  Mesh & Mesh::operator =(Mesh && other)
  {
    Clear();
    m_vertices = std::move(other.m_vertices);
    m_vertexArray = std::move(other.m_vertexArray);
    m_indexBuffer = std::move(other.m_indexBuffer);
    m_vertexBuffer = std::move(other.m_vertexBuffer);
    return *this;
  }

  Mesh::~Mesh() { Clear(); }

  void Mesh::Bind() const
  {
    m_vertexArray.Bind();
    m_indexBuffer.Bind();
  }

  void Mesh::Unbind() const
  {
    m_vertexArray.Unbind();
    m_indexBuffer.Unbind();
  }

  void Mesh::Clear()
  {
    FreeMemory();
    m_vertexArray.Clear();
    m_vertexBuffer.Clear();
    m_indexBuffer.Clear();
  }

  void Mesh::FreeMemory()
  {
    m_vertices.clear();
  }

  void Mesh::SetVertices(const std::vector<MeshVertex> & vertices)
  {
    m_vertices.clear();
    m_vertices.reserve(vertices.size() * 8); // resize only once at the beginning
    for (const auto & vert : vertices)
    {
      PushVertex(vert);
    }
    InitVertexArray();
  }

  void Mesh::SetVertices(const MeshVertex * vertices, unsigned int count)
  {
    m_vertices.clear();
    m_vertices.reserve(count * 8); // resize only once at the beginning
    for (unsigned int i = 0; i < count; ++i)
    {
      PushVertex(vertices[i]);
    }
    InitVertexArray();
  }

  void Mesh::SetIndices(const GLuint * indices, unsigned int indicesCount)
  {
    m_indexBuffer = IndexBuffer(indices, indicesCount);
  }

  unsigned int Mesh::GetIndicesCount() const { return m_indexBuffer.GetIndicesCount(); }

  void Mesh::InitVertexArray()
  {
    m_vertexArray.Clear();
    m_vertexBuffer.Clear();
    m_vertexBuffer = VertexBuffer(&m_vertices[0], sizeof(GLfloat) * m_vertices.size());
    VertexBufferLayout layout;
    layout.Add<GLfloat>(3);
    layout.Add<GLfloat>(3);
    layout.Add<GLfloat>(2);
    m_vertexArray.AddBuffer(m_vertexBuffer, layout);
    m_vertexArray.Unbind();
  }

  void Mesh::PushVertex(const MeshVertex & vert)
  {
    m_vertices.push_back(vert.m_position.x);
    m_vertices.push_back(vert.m_position.y);
    m_vertices.push_back(vert.m_position.z);
    m_vertices.push_back(vert.m_normal.x);
    m_vertices.push_back(vert.m_normal.y);
    m_vertices.push_back(vert.m_normal.z);
    m_vertices.push_back(vert.m_uv.x);
    m_vertices.push_back(vert.m_uv.y);
  }
}
