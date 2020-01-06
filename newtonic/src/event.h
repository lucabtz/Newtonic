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
    KeyDown, KeyUp, KeyRepeat, MouseMove, MouseClick, MouseRelease, MouseScroll
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

  /**
   * Event fired when the window framebuffer size changes
   */
  class WindowResizeEvent : public Event
  {
  public:
    WindowResizeEvent(const Viewport & oldViewport, const Viewport & newViewport);

    std::string GetLogMessage() const override;
    /** Returns the new framebuffer viewport */
    const Viewport & GetNewViewport() const;
    /** Returns the old framebuffer viewport */
    const Viewport & GetOldViewport() const;
  private:
    Viewport m_old;
    Viewport m_new;
  };

  /**
   * Event fired when the window close button is pressed
   */
  class WindowCloseEvent : public Event
  {
  public:
    WindowCloseEvent();
    std::string GetLogMessage() const override;
  };

  /**
   * Event fired when a key is pressed
   */
  class KeyDownEvent : public Event
  {
  public:
    KeyDownEvent(unsigned int keyCode);

    std::string GetLogMessage() const override;
    /** Returns the keycode */
    unsigned int GetKeyCode() const;

  private:
    unsigned int m_keyCode;
  };

  /**
   * Event fired when a key is released
   */
  class KeyUpEvent : public Event
  {
  public:
    KeyUpEvent(unsigned int keyCode);

    std::string GetLogMessage() const override;
    /** Returns the keycode */
    unsigned int GetKeyCode() const;

  private:
    unsigned int m_keyCode;
  };

  /**
   * Event fired when a key is held down
   * The event gets fired until the key goes up again
   */
  class KeyRepeatEvent : public Event
  {
  public:
    KeyRepeatEvent(unsigned int keyCode, unsigned int times);

    std::string GetLogMessage() const override;
    /** Returns the keycode */
    unsigned int GetKeyCode() const;
    unsigned int GetTimes() const;
  private:
    unsigned int m_keyCode;
    unsigned int m_times;
  };

  /**
   * Event fired when the mouse moves in the window frame
   */
  class MouseMoveEvent : public Event
  {
  public:
    MouseMoveEvent(const Vector2 & position);

    std::string GetLogMessage() const override;
    /** Returns the mouse position */
    const Vector2 & GetPosition() const;
  private:
    Vector2 m_position;
  };

  /**
   * Event fired when a mouse button is clicked
   */
  class MouseClickEvent : public Event
  {
  public:
    MouseClickEvent(unsigned int button);

    std::string GetLogMessage() const override;
    /** Returns the button code */
    unsigned int GetButton() const;
  private:
    unsigned int m_button;
  };

  /**
   * Event fired when a mouse button is released
   */
  class MouseReleaseEvent : public Event
  {
  public:
    MouseReleaseEvent(unsigned int button);

    std::string GetLogMessage() const override;
    /** Returns the button code */
    unsigned int GetButton() const;
  private:
    unsigned int m_button;
  };

  /**
   * Event fired when the user scrolls with their mouse in the window frame
   */
  class MouseScrollEvent : public Event
  {
  public:
    MouseScrollEvent(float xOffset, float yOffset);

    std::string GetLogMessage() const override;
    /** Returns how much the mouse has scrolled in the X direction. Probably not of interest for most applications */
    float GetXOffset() const;
    /** Returns how much the mouse has scrolled in the Y direction */
    float GetYOffset() const;
  private:
    float m_xOffset;
    float m_yOffset;
  };
}
