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

#include <string>
#include "window.h"
#include "logger.h"

namespace Newtonic
{
  class Application
  {
  public:
    Application(std::string name, const Viewport & viewport);
    virtual ~Application();

    const std::string & GetName() const;
    Window & GetWindow();
    const Logger & GetLogger() const;

    void Stop();
    void Start();

    virtual void Setup() = 0;
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
  private:
    std::string m_name;
    Window m_window;
    bool m_running;
  };
}
