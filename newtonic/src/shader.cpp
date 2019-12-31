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

#include "shader.h"

#include "core.h"
#include "util.h"
#include "opengl.h"

#include <string.h>
#include <vector>

#include <iostream>

namespace Newtonic
{
  static bool CompileShader(GLuint shaderId, const char * shaderCode, size_t codeLen)
  {
    GLint result = 0;
    GLint infoLogLen = 0;
    NW_WRAP_GL_CALL(glShaderSource(shaderId, 1, &shaderCode, NULL));
    NW_WRAP_GL_CALL(glCompileShader(shaderId));

    NW_WRAP_GL_CALL(glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result));
    NW_WRAP_GL_CALL(glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLen));

    if (infoLogLen > 0)
    {
      std::vector<char> log(infoLogLen + 1);
      log[infoLogLen] = '\0';
      NW_WRAP_GL_CALL(glGetShaderInfoLog(shaderId, infoLogLen, nullptr, &log[0]));
      Core::GetCoreLogger().Error(FormatString("Error compiling shader: %s", &log[0]));
      return false;
    }
    return true;
  }

  Shader::Shader() : m_shaderId(INVALID_SHADER_ID) {}
  Shader::Shader(GLuint id) : m_shaderId(id) { NW_WRAP_DEBUG(Core::GetCoreLogger().Debug(FormatString("Created shader %i", m_shaderId))); }
  Shader::~Shader() { if (m_shaderId != INVALID_SHADER_ID) { NW_WRAP_GL_CALL(glDeleteProgram(m_shaderId)); } }

  Shader::Shader(Shader && other) :
    m_shaderId(other.m_shaderId)
  {
    other.m_shaderId = INVALID_SHADER_ID;
  }

  Shader & Shader::operator =(Shader && other)
  {
    if (m_shaderId != INVALID_SHADER_ID)
    {
      NW_WRAP_GL_CALL(glDeleteProgram(m_shaderId));
    }
    m_shaderId = other.m_shaderId;
    other.m_shaderId = INVALID_SHADER_ID;
    return *this;
  }

  void Shader::Bind()   const { NW_WRAP_GL_CALL(glUseProgram(m_shaderId)); }
  void Shader::Unbind() const { NW_WRAP_GL_CALL(glUseProgram(0));          }

  int Shader::GetUniformLocation(const std::string & name) const
  {
    Bind();
    NW_WRAP_GL_CALL(int loc = glGetUniformLocation(m_shaderId, name.c_str()));
    if (loc == -1)
    {
      Core::GetCoreLogger().Error(FormatString("Uniform %s not found in shader %i. Aborting", name.c_str(), m_shaderId));
      ASSERT_TRUE(false);
    }

    return loc;
  }

  void Shader::LoadUniform1f(const std::string & name, GLfloat v) const
  {
    int loc = GetUniformLocation(name);
    NW_WRAP_GL_CALL(glUniform1f(loc, v));
  }

  void Shader::LoadUniform2f(const std::string & name, GLfloat v1, GLfloat v2) const
  {
    int loc = GetUniformLocation(name);
    NW_WRAP_GL_CALL(glUniform2f(loc, v1, v2));
  }

  void Shader::LoadUniform3f(const std::string & name, GLfloat v1, GLfloat v2, GLfloat v3) const
  {
    int loc = GetUniformLocation(name);
    NW_WRAP_GL_CALL(glUniform3f(loc, v1, v2, v3));
  }

  void Shader::LoadUniform4f(const std::string & name, GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4) const
  {
    int loc = GetUniformLocation(name);
    NW_WRAP_GL_CALL(glUniform4f(loc, v1, v2, v3, v4));
  }

  void Shader::LoadMatrix4(const std::string & name, const Matrix4 & mat) const
  {
    int loc = GetUniformLocation(name);
    NW_WRAP_GL_CALL(glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat)));
  }

  Shader Shader::CreateShader(const char * vertex, const char * fragment)
  {
    size_t vertexLen = strlen(vertex);
    size_t fragmentLen = strlen(fragment);

    NW_WRAP_DEBUG(Core::GetCoreLogger().Debug(Newtonic::FormatString("Compiling shader vertex:\n %s \nfragment: \n %s", vertex, fragment)));
    NW_WRAP_DEBUG(Core::GetCoreLogger().Debug(Newtonic::FormatString("Vertex len: %i, fragment len: %i", vertexLen, fragmentLen)));

    NW_WRAP_GL_CALL(GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER));
    NW_WRAP_GL_CALL(GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER));
    NW_WRAP_GL_CALL(GLuint shaderProgram = glCreateProgram());

    if (!CompileShader(vertexShader, vertex, vertexLen)) throw std::runtime_error("Cannot compile vertex shader");
    if (!CompileShader(fragmentShader, fragment, fragmentLen)) throw std::runtime_error("Cannot compile fragment shader");

    NW_WRAP_GL_CALL(glAttachShader(shaderProgram, vertexShader));
    NW_WRAP_GL_CALL(glAttachShader(shaderProgram, fragmentShader));

    NW_WRAP_GL_CALL(glLinkProgram(shaderProgram));

    GLint logLen = 0;

    NW_WRAP_GL_CALL(glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &logLen));

    if (logLen > 0)
    {
      std::vector<char> log(logLen + 1);
      log[logLen] = '\0';
      NW_WRAP_GL_CALL(glGetProgramInfoLog(shaderProgram, logLen, nullptr, &log[0]));
      Core::GetCoreLogger().Error(FormatString("Error linking shader: %s", &log[0]));
    }

    NW_WRAP_DEBUG(Core::GetCoreLogger().Debug(Newtonic::FormatString("Shader created", vertexLen, fragmentLen)));

    return Shader(shaderProgram);
  }

}
