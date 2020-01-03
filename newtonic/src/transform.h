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
    Transform();
    Transform(const Transform & other);
    Transform & operator =(const Transform & other);

    Matrix4 GetMatrix() const;

    Matrix4 GetTranslationMatrix() const;
    Matrix4 GetRotationMatrix() const;
    Matrix4 GetScaleMatrix() const;

    const Vector3 & GetPosition() const;
    const Quaternion & GetRotation() const;
    const Vector3 & GetScale() const;

    Vector3 GetForwardDirection() const;
    Vector3 GetTopDirection() const;
    Vector3 GetRightDirection() const;

    void Translate(const Vector3 & translation);
    void Rotate(const Quaternion & rotation);
    void Scale(const Vector3 & scale);

    void SetPosition(const Vector3 & position);
    void SetRoation(const Quaternion & rotation);
    void SetScale(const Vector3 & scale);
  private:
    Vector3 m_position;
    Quaternion m_rotation;
    Vector3 m_scale;
  };
}
