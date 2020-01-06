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

#include "math.h"

#define HIGHEST_KEY_CODE 500
#define HIGHEST_BUTTON_CODE 10

namespace Newtonic
{
  enum class MouseAxis : unsigned int
  {
    Horizontal, Vertical
  };

  class Input
  {
  public:
    static void Init();

    static bool IsKeyDown(unsigned int keyCode);
    static bool IsKeyUp(unsigned int keyCode) { return !IsKeyDown(keyCode); }

    static bool IsButtonDown(unsigned int buttonCode);
    static bool IsButtonUp(unsigned int buttonCode) { return !IsButtonDown(buttonCode); }

    /**
     * Returns the mouse position on the given axis
     */
    static float GetAxis(MouseAxis axis);
  private:
    static bool s_keyStatuses[HIGHEST_KEY_CODE];
    static bool s_buttonStatuses[HIGHEST_BUTTON_CODE];

    static Vector2 s_mousePosition;
  };
}
