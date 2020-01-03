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

#include "viewport.h"
#include "math.h"

namespace Newtonic
{
  enum class EventType : unsigned int
  {
    Invalid,
    WindowResize, WindowClose,
    KeyDown, KeyUp, KeyRepeat, MouseMove, MouseClick
  };

  class Event
  {
  public:
    Event(EventType type);

    EventType GetType() const;
    virtual std::string GetLogMessage() const;
  private:
    EventType m_type;
  };

  class WindowResizeEvent : public Event
  {
  public:
    WindowResizeEvent(const Viewport & oldViewport, const Viewport & newViewport);

    std::string GetLogMessage() const override;
    const Viewport & GetNewViewport() const;
    const Viewport & GetOldViewport() const;
  private:
    Viewport m_old;
    Viewport m_new;
  };

  class WindowCloseEvent : public Event
  {
  public:
    WindowCloseEvent();
    std::string GetLogMessage() const override;
  };

  class KeyDownEvent : public Event
  {
  public:
    KeyDownEvent(unsigned int keyCode);

    std::string GetLogMessage() const override;
    unsigned int GetKeyCode() const;

  private:
    unsigned int m_keyCode;
  };

  class KeyUpEvent : public Event
  {
  public:
    KeyUpEvent(unsigned int keyCode);

    std::string GetLogMessage() const override;
    unsigned int GetKeyCode() const;

  private:
    unsigned int m_keyCode;
  };

  class KeyRepeatEvent : public Event
  {
  public:
    KeyRepeatEvent(unsigned int keyCode, unsigned int times);

    std::string GetLogMessage() const override;
    unsigned int GetKeyCode() const;
    unsigned int GetTimes() const;
  private:
    unsigned int m_keyCode;
    unsigned int m_times;
  };

  class MouseMoveEvent : public Event
  {
  public:
    MouseMoveEvent(const Vector2 & position);

    std::string GetLogMessage() const override;
    const Vector2 & GetPosition() const;
  private:
    Vector2 m_position;
  };

  class MouseClickEvent : public Event
  {
  public:
    MouseClickEvent(unsigned int button);

    std::string GetLogMessage() const override;
    unsigned int GetButton() const;
  private:
    unsigned int m_button;
  };
}
