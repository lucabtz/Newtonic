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

#include "../math.h"

namespace Newtonic
{
  class Camera
  {
  public:
    virtual Matrix4 GetViewMatrix() const = 0;
    virtual Matrix4 GetProjectionMatrix() const = 0;

    virtual Vector3 GetViewDirection() const = 0;
    virtual Vector3 GetTopDirection() const = 0;
    virtual Vector3 GetRightDirection() const = 0;
  };
}
