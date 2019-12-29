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

#include <iostream>
#include <GL/glew.h>

#include "core.h"
#include "util.h"

static void ClearOpenGLErrorState() { while (glGetError() != GL_NO_ERROR); }
static bool LogOpenGLErrorState(const char * expr, const char * file, int line)
{
  GLenum error = glGetError();
  if (error)
  {
    Newtonic::Core::GetCoreLogger().Error(Newtonic::FormatString("%i %s %s:%i", error, expr, file, line));
    return true;
  }
  return false;
}

#define NW_WRAP_GL_CALL(x) ClearOpenGLErrorState();\
  x;\
  ASSERT_FALSE(LogOpenGLErrorState(#x, __FILE__, __LINE__))
