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

#include "camera.h"

#include "viewport.h"

namespace Newtonic
{
  class PerspectiveCamera  : public Camera
  {
  public:
    PerspectiveCamera();
    PerspectiveCamera(const Vector3 & position, const Vector3 & target, const Vector3 & up,
                      float fovY, float aspect, float zNear, float zFar);
    PerspectiveCamera(const PerspectiveCamera & other);
    PerspectiveCamera & operator =(const PerspectiveCamera & other);

    void SetAspectRatio(const Viewport & viewport);
    void SetFOV(float fov);
    void SetZNear(float zNear);
    void SetZFar(float zFar);

    Matrix4 GetViewMatrix() const override;
    Matrix4 GetProjectionMatrix() const override;

    Vector3 GetViewDirection() const override;
    Vector3 GetTopDirection() const override;
    Vector3 GetRightDirection() const override;

    void SetPosition(const Vector3 & position);
    void LookAt(const Vector3 & target);
    void SetUpDirection(const Vector3 & up);

  private:
    Vector3 m_position;
    Vector3 m_target;
    Vector3 m_up;

    float m_fovY;
    float m_aspect;
    float m_zNear;
    float m_zFar;
  };
}
