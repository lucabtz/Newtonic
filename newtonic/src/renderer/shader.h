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

#include "opengl.h"
#include "../math.h"

#include <string>

#define INVALID_SHADER_ID 0

namespace Newtonic
{
  class Shader
  {
  public:
    Shader();
    Shader(GLuint id);
    ~Shader();
    Shader(Shader && other);
    Shader & operator =(Shader && other);

    void Bind() const;
    void Unbind() const;

    void LoadUniform1f(const std::string & name, GLfloat v) const;
    void LoadUniform2f(const std::string & name, GLfloat v1, GLfloat v2) const;
    void LoadUniform3f(const std::string & name, GLfloat v1, GLfloat v2, GLfloat v3) const;
    void LoadUniform4f(const std::string & name, GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4) const;
    void LoadUniform1i(const std::string & name, GLint v) const;

    void LoadFloat(const std::string & name, GLfloat v) const { LoadUniform1f(name, v); }
    void LoadVector2(const std::string & name, const Vector2 & vec) const { LoadUniform2f(name, vec.x, vec.y); }
    void LoadVector3(const std::string & name, const Vector3 & vec) const { LoadUniform3f(name, vec.x, vec.y, vec.z); }
    void LoadVector4(const std::string & name, const Vector4 & vec) const { LoadUniform4f(name, vec.x, vec.y, vec.z, vec.w); }
    void LoadMatrix4(const std::string & name, const Matrix4 & mat) const;

    static Shader CreateShader(const char * vertex, const char * fragment);

  private:
    GLuint m_shaderId;

    int GetUniformLocation(const std::string & name) const;
  };
}
