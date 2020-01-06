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

#include "vertexarray.h"
#include "indexbuffer.h"
#include "meshvertex.h"

#include "../math.h"

#include <vector>

namespace Newtonic
{
  class Mesh
  {
  public:
    Mesh();
    Mesh(Mesh && other);
    Mesh & operator =(Mesh && other);
    ~Mesh();

    void Bind() const;
    void Unbind() const;

    void Clear();

    void FreeMemory();

    void SetVertices(const std::vector<MeshVertex> & vertices);
    void SetVertices(const MeshVertex * vertices, unsigned int count);
    void SetIndices(const GLuint * indices, unsigned int count);

    unsigned int GetIndicesCount() const;

  private:
    std::vector<GLfloat> m_vertices;

    VertexArray m_vertexArray;
    VertexBuffer m_vertexBuffer;
    IndexBuffer m_indexBuffer;

    void PushVertex(const MeshVertex & vert);
    void InitVertexArray();
  };
}
