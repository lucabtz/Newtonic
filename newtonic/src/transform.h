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

namespace Newtonic
{
  class Transform
  {
  public:
    Transform() :
      m_position(0.0, 0.0, 0.0),
      m_rotation(0.0, 1.0, 0.0, 0.0),
      m_scale(1.0, 1.0, 1.0)
    {}
    Vector3 GetPosition();
    Vector3 GetRotationEulerAngles();
    Vector3 GetScale();
    Quaternion GetRotation();

    void SetPosition(const Vector3 & newPosition);
    void SetRotationEulerAngles(const Vector3 & newRotation);
    void SetScale(const Vector3 & newScale);

    Matrix4 GetTransformationMatrix();
    Matrix4 GetRotationMatrix();
    Matrix4 GetTranslationMatrix();
    Matrix4 GetScaleMatrix();

    Vector3 GetForwardDirection();
    Vector3 GetRightDirection();
    Vector3 GetUpDirection();

  private:
    Vector3 m_position;
    Quaternion m_rotation;
    Vector3 m_scale;
  };
}
