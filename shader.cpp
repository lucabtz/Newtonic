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

#include "shader.h"

#include "common.h"

#include <stdio.h>
#include <iostream>
#include <vector>

 namespace Newtonic
 {

   void CompileShader(GLuint shaderId, std::string &shaderCode)
   {
     GLint result = 0;
     int infoLogLen = 0;
     const char * const pShaderCode = shaderCode.c_str();
     glShaderSource(shaderId, 1, &pShaderCode, NULL);
     glCompileShader(shaderId);

     glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
     glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLen);

     if (infoLogLen > 0)
     {
       std::vector<char> log(infoLogLen + 1);
       log[infoLogLen] = '\0';
       glGetShaderInfoLog(shaderId, infoLogLen, NULL, &log[0]);
       printf("[SHADER] [Compile Log] %s\n", &log[0]);
     }
   }

   Shader::Shader(const char * vertShader, const char* fragShader)
   {
     GLuint vertShaderId = glCreateShader(GL_VERTEX_SHADER);
     GLuint fragShaderId = glCreateShader(GL_FRAGMENT_SHADER);

     std::string vertShaderCode;
     std::string fragShaderCode;

     try
     {
       vertShaderCode = ReadFile(vertShader);
       fragShaderCode = ReadFile(fragShader);
     }
     catch (NewtonicException &e)
     {
       printf("[SHADER] [ERROR] Cannot load shader: %s %s\n", vertShader, fragShader);
       printf("%s\n", e.what());
       throw e;
     }

     printf("[SHADER] Compiling vertex shader %s\n", vertShader);
     CompileShader(vertShaderId, vertShaderCode);

     printf("[SHADER] Compiling fragment shader %s\n", fragShader);
     CompileShader(fragShaderId, fragShaderCode);

     GLuint shaderProgramId = glCreateProgram();
     glAttachShader(shaderProgramId, vertShaderId);
     glAttachShader(shaderProgramId, fragShaderId);

     printf("[SHADER] Linking shader program\n");
     glLinkProgram(shaderProgramId);

     GLint res = 0;
     int logLen = 0;

     glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &res);
     glGetProgramiv(shaderProgramId, GL_INFO_LOG_LENGTH, &logLen);

     if (logLen > 0)
     {
       std::vector<char> log(logLen + 1);
       log[logLen] = '\0';
       glGetProgramInfoLog(shaderProgramId, logLen, NULL, &log[0]);
       printf("[SHADER] [Link log] %s\n", &log[0]);
     }

     glDetachShader(shaderProgramId, vertShaderId);
     glDetachShader(shaderProgramId, fragShaderId);

     m_shaderId = shaderProgramId;

     Init();
   }

   GLuint Shader::GetShaderId() const { return m_shaderId; }
   void Shader::UseShader() const { glUseProgram(GetShaderId()); }
   void Shader::StopShader() const { glUseProgram(0); }

 }
