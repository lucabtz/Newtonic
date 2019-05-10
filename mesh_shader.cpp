/*
 *   Newtonic - Graphics for Physics
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

#include "mesh_shader.h"

namespace Newtonic
{
  MeshShader::MeshShader(
    std::string vertShader,
    std::string fragShader,
    std::string modelMatrixUniformName,
    std::string viewMatrixUniformName,
    std::string projectionMatrixUniformName
  ) :
    Shader(vertShader.c_str(), fragShader.c_str()),
    m_modelMatrixUniformName(modelMatrixUniformName),
    m_viewMatrixUniformName(viewMatrixUniformName),
    m_projectionMatrixUniformName(projectionMatrixUniformName)
  {};

  void MeshShader::Init()
  {
    m_modlLoc = glGetUniformLocation(GetShaderId(), m_modelMatrixUniformName.c_str());
    m_viewLoc = glGetUniformLocation(GetShaderId(), m_viewMatrixUniformName.c_str());
    m_projLoc = glGetUniformLocation(GetShaderId(), m_projectionMatrixUniformName.c_str());
  }

  void MeshShader::SetModel(glm::mat4 model)
  {
    glUniformMatrix4fv(m_modlLoc, 1, GL_FALSE, &model[0][0]);
  }

  void MeshShader::SetView(glm::mat4 view)
  {
    glUniformMatrix4fv(m_viewLoc, 1, GL_FALSE, &view[0][0]);
  }

  void MeshShader::SetProj(glm::mat4 proj)
  {
    glUniformMatrix4fv(m_projLoc, 1, GL_FALSE, &proj[0][0]);
  }

}
