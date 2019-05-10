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

#include "assets.h"
#include "mesh.h"
#include "shader.h"

 namespace Newtonic
 {
   void Assets::LoadShader(
     std::string shaderName,
     const char * vertexShader,
     const char * fragmentShader)
  {
    m_shaders.emplace(shaderName, std::make_shared<Shader>(vertexShader, fragmentShader));
  }

  void Assets::LoadShaderT(
    std::string shaderName,
    std::shared_ptr<Shader> pShader)
  {
    m_shaders.emplace(shaderName, pShader);
  }

  void Assets::LoadMesh(
    std::string meshName,
    const std::vector<GLfloat> & positions)
  {
    m_meshes.emplace(meshName, std::make_shared<Mesh>(positions));
  }

 }
