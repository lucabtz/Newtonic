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
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>


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
    void LoadShaderT(std::string shaderName, std::shared_ptr<Shader> pShader);
    void LoadMesh(std::string meshName, const std::vector<GLfloat> & positions, const std::vector<unsigned int> & indices);
    void LoadMeshesFromOBJ(std::string filename);

    std::weak_ptr<Shader> GetShader(std::string name)
    {
      std::weak_ptr<Shader> wpShader = m_shaders[name];
      return wpShader;
    }

    std::weak_ptr<Mesh> GetMesh(std::string name)
    {
      std::weak_ptr<Mesh> wpMesh = m_meshes[name];
      return wpMesh;
    }

    template <typename ShaderT>
    std::weak_ptr<ShaderT> GetShaderT(std::string name)
    {
      std::shared_ptr<Shader> pShader = m_shaders[name];
      std::shared_ptr<ShaderT> pDownCasted =
                std::dynamic_pointer_cast<ShaderT>(pShader);
      return pDownCasted;
    }

    ~Assets() { std::cout << "[LOADER] Freeing assets manager" << std::endl; }
  };

}


#endif // _ASSETS_H
