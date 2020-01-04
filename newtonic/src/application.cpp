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

#include "application.h"
#include "timestep.h"
#include "core.h"
#include "input.h"
#include "eventbus.h"

namespace Newtonic
{
  Application::Application(std::string name, const Viewport & viewport) : m_name(name), m_window(Window::CreateWindow(name.c_str(), viewport)), m_running(false)
  { Core::PostWindowInit(); }
  Application::~Application() {}

  const std::string & Application::GetName() const { return m_name; }
  Window & Application::GetWindow() { return m_window; }
  const Logger & Application::GetLogger() const { return Core::GetApplicationLogger(); }

  void Application::Stop() { m_running = false; }

  void Application::Start()
  {
    Input::Init();
    m_running = true;
    Setup();
    Timestep time;
    while (m_running)
    {
      float dt = time.DeltaTime();
      Update(dt);
      Render();
      m_window.Update();
      EventBus::DispatchAll();
    }
  }

}
