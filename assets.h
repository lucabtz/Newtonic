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

#ifndef _ASSETS_H
#define _ASSETS_H

#include <vector>
#include <memory>
#include <map>
#include <string>

namespace Newtonic
{

  class Mesh;
  class Shader;

  class Assets
  {
    std::map<std::string, std::shared_ptr<Shader>> m_shaders;
    std::map<std::string, std::shared_ptr<Mesh>> m_meshes;

  public:
    void LoadShader(std::string shaderName, const char * vertexShader, const char * fragmentShader);
    void LoadMesh(std::string meshName, const std::vector<GLfloat> & positions);

    std::weak_ptr<Shader> GetShader(std::string name);
    std::weak_ptr<Mesh> GetMesh(std::string name);

  };

}


#endif // _ASSETS_H
