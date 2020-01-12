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

#include "event.h"

#include "util.h"

namespace Newtonic
{
  Event::Event(EventType type) : m_type(type) {}
  Event::~Event() {}
  EventType Event::GetType() const { return m_type; }
  std::string Event::GetLogMessage() const { return FormatString("Event %i", m_type); }

  WindowResizeEvent::WindowResizeEvent(const Viewport & oldViewport, const Viewport & newViewport)
    : Event(EventType::WindowResize), m_old(oldViewport), m_new(newViewport)
  {}
  std::string WindowResizeEvent::GetLogMessage() const { return FormatString("WindowResizeEvent(from: (%i, %i), to: (%i, %i))", m_old.m_width, m_old.m_height, m_new.m_width, m_new.m_height); }
  const Viewport & WindowResizeEvent::GetNewViewport() const { return m_new; }
  const Viewport & WindowResizeEvent::GetOldViewport() const { return m_old; }

  WindowCloseEvent::WindowCloseEvent() : Event(EventType::WindowClose) {}
  std::string WindowCloseEvent::GetLogMessage() const { return FormatString("WindowCloseEvent"); }

  KeyDownEvent::KeyDownEvent(unsigned int keyCode) : Event(EventType::KeyDown), m_keyCode(keyCode) {}
  std::string KeyDownEvent::GetLogMessage() const { return FormatString("KeyDownEvent(key: %i)", m_keyCode); }
  unsigned int KeyDownEvent::GetKeyCode() const { return m_keyCode; }

  KeyUpEvent::KeyUpEvent(unsigned int keyCode) : Event(EventType::KeyUp), m_keyCode(keyCode) {}
  std::string KeyUpEvent::GetLogMessage() const { return FormatString("KeyUpEvent(key: %i)", m_keyCode); }
  unsigned int KeyUpEvent::GetKeyCode() const { return m_keyCode; }

  KeyRepeatEvent::KeyRepeatEvent(unsigned int keyCode, unsigned int times) : Event(EventType::KeyRepeat), m_keyCode(keyCode), m_times(times) {}
  std::string KeyRepeatEvent::GetLogMessage() const { return FormatString("KeyRepeatEvent(key: %i, times: %i)", m_keyCode, m_times); }
  unsigned int KeyRepeatEvent::GetKeyCode() const { return m_keyCode; }
  unsigned int KeyRepeatEvent::GetTimes() const { return m_times; }

  MouseMoveEvent::MouseMoveEvent(const Vector2 & position) : Event(EventType::MouseMove), m_position(position) {}
  std::string MouseMoveEvent::GetLogMessage() const { return FormatString("MouseMoveEvent(position: (%f, %f))", m_position.x, m_position.y); }
  const Vector2 & MouseMoveEvent::GetPosition() const { return m_position; }

  MouseClickEvent::MouseClickEvent(unsigned int button) : Event(EventType::MouseClick), m_button(button) {}
  std::string MouseClickEvent::GetLogMessage() const { return FormatString("MouseClickEvent(button: %i)", m_button); }
  unsigned int MouseClickEvent::GetButton() const { return m_button; }

  MouseReleaseEvent::MouseReleaseEvent(unsigned int button) : Event(EventType::MouseRelease), m_button(button) {}
  std::string MouseReleaseEvent::GetLogMessage() const { return FormatString("MouseReleaseEvent(button: %i)", m_button); }
  unsigned int MouseReleaseEvent::GetButton() const { return m_button; }

  MouseScrollEvent::MouseScrollEvent(float xOffset, float yOffset) : Event(EventType::MouseScroll), m_xOffset(xOffset), m_yOffset(yOffset) {}
  std::string MouseScrollEvent::GetLogMessage() const { return FormatString("MouseScrollEvent(xOffset: %f, yOffset: %f)", m_xOffset, m_yOffset); }
  float MouseScrollEvent::GetXOffset() const { return m_xOffset; }
  float MouseScrollEvent::GetYOffset() const { return m_yOffset; }
}
