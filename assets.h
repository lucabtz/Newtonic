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
    /**
     * Loads a shader resource
     * @param shaderName     the shader's name to be assigned to the resource
     * @param vertexShader   the vertex shader file location
     * @param fragmentShader the fragment shader file location
     */
    void LoadShader(std::string shaderName, const char * vertexShader, const char * fragmentShader);
    /**
     * Loads an already constructed shader as a resource
     * @param shaderName the name to be assigned to the resource
     * @param pShader    a shared_ptr to a Shader object
     */
    void LoadShaderT(std::string shaderName, std::shared_ptr<Shader> pShader);
    /**
     * Loads a mesh resource
     * @param meshName  the resource name
     * @param positions the vertex positions as vector<GLfloat>
     * @param indices   the indices as vector<unsigned int>
     */
    void LoadMesh(std::string meshName, const std::vector<GLfloat> & positions, const std::vector<unsigned int> & indices);
    /**
     * Uses OBJ_Loader.h to load the meshes from a file
     * @param filename the file location
     */
    void LoadMeshesFromOBJ(std::string filename);

    /**
     * Getter for a specific shader resource
     * @param  name the resource name
     * @return      a weak_ptr to the resource if found
     */
    std::weak_ptr<Shader> GetShader(std::string name)
    {
      std::weak_ptr<Shader> wpShader = m_shaders[name];
      return wpShader;
    }

    /**
     * Getter for a specific mesh resource
     * @param  name the resource name
     * @return      a weak_ptr to the resource if found
     */
    std::weak_ptr<Mesh> GetMesh(std::string name)
    {
      std::weak_ptr<Mesh> wpMesh = m_meshes[name];
      return wpMesh;
    }

    /**
     * Getter for a shader resource. Casts the shader to the given template argument dynamically
     * @param  name the resource name
     * @return      a weak_ptr to the given template argument
     */
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
