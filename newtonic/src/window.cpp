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


#include "window.h"

#include "util.h"
#include "eventbus.h"

namespace Newtonic
{
  Window::Window() : m_window(nullptr), m_windowData(), m_stickCursorToCenter(false) {}

  Window::Window(Window && other) : m_window(other.m_window), m_windowData(other.m_windowData)
  {
    other.m_window = nullptr;
  }

  Window & Window::operator =(Window && other)
  {
    if (m_window != nullptr) glfwDestroyWindow(m_window);
    m_window = other.m_window;
    other.m_window = nullptr;
    m_windowData = other.m_windowData;
    return *this;
  }

  Window::~Window() { if (m_window != nullptr) glfwDestroyWindow(m_window); }

  void Window::MakeCurrent() const { glfwMakeContextCurrent(m_window); }
  bool Window::ShouldClose() const { return glfwWindowShouldClose(m_window); }
  void Window::SwapBuffers()  const { glfwSwapBuffers(m_window); }
  void Window::PollEvents()  const { glfwPollEvents(); }
  Viewport Window::GetViewport() const { return m_windowData.m_viewport; }
  void Window::StickCursorToCenter(bool value) { m_stickCursorToCenter = value; }

  void Window::Update()
  {
    if (m_stickCursorToCenter)
    {
      double centerX = m_windowData.m_viewport.m_width / 2;
      double centerY = m_windowData.m_viewport.m_height / 2;

      glfwSetCursorPos(m_window, centerX, centerY);
    }
    SwapBuffers();
    PollEvents();
  }

  void Window::HideCursor(bool value) const
  {
    if (value) glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    else       glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  }

  void Window::SetStickyKeys(bool value) const
  {
    if (value) glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);
    else       glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_FALSE);
  }

  Window Window::CreateWindow(const char * title, Viewport viewport)
  {
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow * glfwWindow = glfwCreateWindow(viewport.m_width, viewport.m_height, title, nullptr, nullptr);
    Window window;
    window.m_window = glfwWindow;
    window.m_windowData.m_viewport = viewport;
    window.MakeCurrent();
    glfwSetWindowUserPointer(glfwWindow, &window.m_windowData);

    glfwSetFramebufferSizeCallback(glfwWindow, [](GLFWwindow * wnd, int width, int height)
    {
      WindowData & wndData = *(WindowData*)glfwGetWindowUserPointer(wnd);
      EventBus::Push(std::make_shared<WindowResizeEvent>(wndData.m_viewport, Viewport(width, height)));
      wndData.m_viewport = Viewport(width, height);
    });

    glfwSetKeyCallback(glfwWindow, [](GLFWwindow * wnd, int key, int scancode, int action, int mods)
    {
      switch (action)
      {
      case GLFW_PRESS:
        EventBus::Push(std::make_shared<KeyDownEvent>(key));
        break;
      case GLFW_RELEASE:
        EventBus::Push(std::make_shared<KeyUpEvent>(key));
        break;
      case GLFW_REPEAT:
        EventBus::Push(std::make_shared<KeyRepeatEvent>(key, 1));
        break;
      }
    });

    glfwSetMouseButtonCallback(glfwWindow, [](GLFWwindow * wnd, int button, int action, int modes)
    {
      switch (action)
      {
      case GLFW_PRESS:
        EventBus::Push(std::make_shared<MouseClickEvent>(button));
        break;
      case GLFW_RELEASE:
        EventBus::Push(std::make_shared<MouseReleaseEvent>(button));
        break;
      }
    });

    glfwSetScrollCallback(glfwWindow, [](GLFWwindow * wnd, double xOffset, double yOffset)
    {
      EventBus::Push(std::make_shared<MouseScrollEvent>((float)xOffset, (float)yOffset));
    });

    glfwSetCursorPosCallback(glfwWindow, [](GLFWwindow * wnd, double xPos, double yPos)
    {
      EventBus::Push(std::make_shared<MouseMoveEvent>(Vector2((float)xPos, (float)yPos)));
    });

    glfwSetWindowCloseCallback(glfwWindow, [](GLFWwindow * wnd)
    {
      EventBus::Push(std::make_shared<WindowCloseEvent>());
    });

    return window;
  }
}
