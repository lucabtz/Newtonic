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

#include <iostream>

#include "OBJ_Loader.h"

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
    const std::vector<GLfloat> & positions,
    const std::vector<unsigned int> & indices)
  {
    m_meshes.emplace(meshName, std::make_shared<Mesh>(positions, indices));
  }

  void Assets::LoadMeshesFromOBJ(std::string filename)
  {
    objl::Loader loader;
    std::cout << "[LOADER] Loading file " << filename << std::endl;
    bool success = loader.LoadFile(filename);
    if (success)
    {
        for (int i = 0; i < loader.LoadedMeshes.size(); ++i)
        {
            objl::Mesh currentMesh = loader.LoadedMeshes[i];
            std::cout << "[LOADER] Loaded mesh " << currentMesh.MeshName << std::endl;
            std::vector<objl::Vertex> vertices = loader.LoadedMeshes[i].Vertices;
            std::vector<unsigned int> indices = loader.LoadedMeshes[i].Indices;
            std::vector<GLfloat> glVertices(vertices.size() * 3);
            for (auto & vert : vertices)
            {
              glVertices.push_back(static_cast<GLfloat>(vert.Position.X));
              glVertices.push_back(static_cast<GLfloat>(vert.Position.Y));
              glVertices.push_back(static_cast<GLfloat>(vert.Position.Z));
            }

            auto mesh = std::make_shared<Mesh>(glVertices, indices);
            m_meshes.emplace(currentMesh.MeshName, mesh);
        }
    }
    else
    {
      // TODO handle this
    }
  }

 }
