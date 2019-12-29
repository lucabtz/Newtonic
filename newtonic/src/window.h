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

#include "viewport.h"
#include <GLFW/glfw3.h>

namespace Newtonic
{
  struct WindowData
  {
    Viewport m_viewport;

    WindowData() : m_viewport(0, 0) {}
    WindowData(const WindowData & other) : m_viewport(other.m_viewport) {}
    WindowData * operator =(const WindowData & other) { m_viewport = other.m_viewport; }
  };

  class Window
  {
  public:
    Window();
    Window(Window && other);
    Window & operator =(Window && other);
    ~Window();

    bool ShouldClose() const;
    bool IsValid() const { return m_window != nullptr; }
    void SwapBuffers() const;
    void MakeCurrent() const;
    void PollEvents() const;

    void SetStickyKeys(bool value);

    Viewport GetViewport() const;

    void Update();

    static Window CreateWindow(const char * title, Viewport viewport);
  private:
    GLFWwindow * m_window;
    WindowData m_windowData;
  };
}
