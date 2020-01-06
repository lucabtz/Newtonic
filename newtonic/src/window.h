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
    WindowData & operator =(const WindowData & other) { m_viewport = other.m_viewport; return *this; }
  };

  /**
   * An abstraction for window management. Uses GLFW3 at the moment in the implementation
   */
  class Window
  {
  public:
    /**
     * Constructs a window without creating or opening it. Newtonic::Window::CreateWindow should be used to create and open a new window
     */
    Window();
    Window(Window && other);
    Window & operator =(Window && other);
    ~Window();

    /**
     * Returns true if the window should be closed
     */
    bool ShouldClose() const;

    /**
     * Checks whether this window has been initialized properly
     */
    bool IsValid() const { return m_window != nullptr; }

    /**
     * Swap the graphics buffers
     */
    void SwapBuffers() const;

    /**
     * Makes the window context current
     */
    void MakeCurrent() const;

    /**
     * Polls window events
     */
    void PollEvents() const;

    /**
     * Enables or disables sticky keys
     * SetStickyKeys(true) enables them and SetStickyKeys(false) disables them
     */
    void SetStickyKeys(bool value) const;

    /**
     * HideCursor(true) hides the cursor from the window
     * HideCursor(false) makes it visible again
     */
    void HideCursor(bool value) const;

    /**
     * StickCursorToCenter(true) sticks the cursor position to the center. Useful for FPS like camera controllers
     * StickCursorToCenter(false) diasbles this feature
     */
    void StickCursorToCenter(bool value);

    /**
     * Returns a Newtonic::Viewport with the window framebuffer dimensions
     */
    Viewport GetViewport() const;

    /**
     * Updates the window
     */
    void Update();

    /**
     * Creates a new window with given title and viewport
     */
    static Window CreateWindow(const char * title, Viewport viewport);
  private:
    GLFWwindow * m_window;
    WindowData m_windowData;
    bool m_stickCursorToCenter;
  };
}
