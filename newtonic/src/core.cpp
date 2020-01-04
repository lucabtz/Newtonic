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

#include "core.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "util.h"

namespace Newtonic
{
  Logger Core::s_coreLogger;
  Logger Core::s_applicationLogger;

  static void GLFWErrorHandler(int err, const char * desc)
  {
    Core::GetCoreLogger().Error(FormatString("[GLFW Error] %i %s", err, desc));
  }

  void Core::Init()
  {
    s_coreLogger = Logger("NEWTONIC");
    s_applicationLogger = Logger("NEWTONIC APPLICATION");

    glfwSetErrorCallback(GLFWErrorHandler);
    if (!glfwInit())
    {
      s_coreLogger.Error("Cannot initialize GLFW. Aborting");
      ASSERT_TRUE(false);
    }
  }

  void Core::PostWindowInit()
  {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
      s_coreLogger.Error("Cannot initialize glew");
      ASSERT_TRUE(false);
    }

    s_coreLogger.Info(FormatString("OpenGL version %s vendor %s", glGetString(GL_VERSION), glGetString(GL_VENDOR)));
    s_coreLogger.Info(FormatString("GLSL version %s", glGetString(GL_SHADING_LANGUAGE_VERSION)));
  }

}
