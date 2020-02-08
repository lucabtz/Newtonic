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

#include "renderer/renderer.h"

#include "renderer/opengl.h"
#include "util.h"
#include "core.h"

namespace Newtonic
{
  void Renderer::Clear()
  {
    NW_WRAP_GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
  }

  void Renderer::SetClearColor(const Vector4 & color)
  {
    NW_WRAP_GL_CALL(glClearColor(color.r, color.g, color.b, color.a));
  }

  void Renderer::Render(const VertexArray & va, const IndexBuffer & ib)
  {
    va.Bind();
    ib.Bind();
    NW_WRAP_GL_CALL(glDrawElements(GL_TRIANGLES, ib.GetIndicesCount(), GL_UNSIGNED_INT, nullptr));
  }

  void Renderer::Render(const Mesh & mesh)
  {
    mesh.Bind();
    NW_WRAP_GL_CALL(glDrawElements(GL_TRIANGLES, mesh.GetIndicesCount(), GL_UNSIGNED_INT, nullptr));
  }

  void Renderer::RenderLines(const Mesh & mesh)
  {
    mesh.Bind();
    NW_WRAP_GL_CALL(glDrawElements(GL_LINES, mesh.GetIndicesCount(), GL_UNSIGNED_INT, nullptr));
  }

  void Renderer::RenderLines(const VertexArray & va, const IndexBuffer & ib)
  {
    va.Bind();
    ib.Bind();
    NW_WRAP_GL_CALL(glDrawElements(GL_LINES, ib.GetIndicesCount(), GL_UNSIGNED_INT, nullptr));
  }

  void Renderer::SetViewport(Viewport viewport)
  {
    NW_WRAP_GL_CALL(glViewport(0, 0, viewport.m_width, viewport.m_height));
  }
}
