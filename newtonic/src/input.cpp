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

#include "input.h"

#include "util.h"
#include "core.h"
#include "eventbus.h"

namespace Newtonic
{
  bool Input::s_keyStatuses[HIGHEST_KEY_CODE];
  bool Input::s_buttonStatuses[HIGHEST_BUTTON_CODE];
  Vector2 Input::s_mousePosition;

  void Input::Init()
  {
    EventBus::Listen(EventType::KeyUp, [](std::shared_ptr<Event> e)
    {
      unsigned int keyCode = std::dynamic_pointer_cast<KeyUpEvent>(e)->GetKeyCode();
      s_keyStatuses[keyCode] = false;
    });
    EventBus::Listen(EventType::KeyDown, [](std::shared_ptr<Event> e)
    {
      unsigned int keyCode = std::dynamic_pointer_cast<KeyDownEvent>(e)->GetKeyCode();
      s_keyStatuses[keyCode] = true;
    });
    EventBus::Listen(EventType::MouseClick, [](std::shared_ptr<Event> e)
    {
      unsigned int button = std::dynamic_pointer_cast<MouseClickEvent>(e)->GetButton();
      s_buttonStatuses[button] = true;
    });
    EventBus::Listen(EventType::MouseRelease, [](std::shared_ptr<Event> e)
    {
      unsigned int button = std::dynamic_pointer_cast<MouseReleaseEvent>(e)->GetButton();
      s_buttonStatuses[button] = false;
    });
    EventBus::Listen(EventType::MouseMove, [](std::shared_ptr<Event> e)
    {
      const Vector2 & position = std::dynamic_pointer_cast<MouseMoveEvent>(e)->GetPosition();
      s_mousePosition = position;
    });
  }

  bool Input::IsKeyDown(unsigned int keyCode) { ASSERT_TRUE(keyCode < HIGHEST_KEY_CODE); return s_keyStatuses[keyCode]; }
  bool Input::IsButtonDown(unsigned int buttonCode) { ASSERT_TRUE(buttonCode < HIGHEST_BUTTON_CODE); return s_buttonStatuses[buttonCode]; }

  float Input::GetAxis(MouseAxis axis)
  {
    switch (axis)
    {
    case MouseAxis::Horizontal:
      return s_mousePosition.x;
    case MouseAxis::Vertical:
      return s_mousePosition.y;
    }
    Core::GetCoreLogger().Error("Invalid mouse axis");
    ASSERT_TRUE(false);
  }
}
