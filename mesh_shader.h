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

#ifndef _MESH_SHADER
#define _MESH_SHADER

#include "shader.h"

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace Newtonic
{
  class MeshShader : public Shader
  {
    std::string m_modelMatrixUniformName;
    std::string m_viewMatrixUniformName;
    std::string m_projectionMatrixUniformName;

    GLuint m_modlLoc;
    GLuint m_viewLoc;
    GLuint m_projLoc;

  public:
    MeshShader(
      std::string vertShader,
      std::string fragShader,
      std::string modelMatrixUniformName,
      std::string viewMatrixUniformName,
      std::string projectionMatrixUniformName
    );

    void Init() override;

    void SetModel(glm::mat4  model);
    void SetView(glm::mat4 view);
    void SetProj(glm::mat4 proj);
  };
}

#endif // __MASH_SHADER
