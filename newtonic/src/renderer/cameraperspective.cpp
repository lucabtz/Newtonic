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

#include "cameraperspective.h"

namespace Newtonic
{
  PerspectiveCamera::PerspectiveCamera() : PerspectiveCamera(Vector3(0,0,0), Vector3(0,0,-1), Vector3(0,1,0), 0.0f, 0.0f, 0.0f, 0.0f) {}
  PerspectiveCamera::PerspectiveCamera(const Vector3 & position, const Vector3 & target, const Vector3 & up,
                                        float fovY, float aspect, float zNear, float zFar)
    : m_position(position), m_target(target), m_up(up), m_fovY(fovY), m_aspect(aspect), m_zNear(zNear),
      m_zFar(zFar)
  {}

  PerspectiveCamera::PerspectiveCamera(const PerspectiveCamera & other)
    : m_position(other.m_position), m_target(other.m_target), m_up(other.m_up), m_fovY(other.m_fovY), m_aspect(other.m_aspect),
      m_zNear(other.m_zNear), m_zFar(other.m_zFar)
  {}

  PerspectiveCamera & PerspectiveCamera::operator =(const PerspectiveCamera & other)
  {
    m_position = other.m_position;
    m_target = other.m_target;
    m_up = other.m_up;
    m_fovY = other.m_fovY;
    m_aspect = other.m_aspect;
    m_zNear = other.m_zNear;
    m_zFar = other.m_zFar;
    return *this;
  }

  void PerspectiveCamera::SetAspectRatio(const Viewport & viewport) { m_aspect = (float)viewport.m_width / (float)viewport.m_height; }
  void PerspectiveCamera::SetFOV(float fov) { m_fovY = fov; }
  void PerspectiveCamera::SetZNear(float zNear) { m_zNear = zNear; }
  void PerspectiveCamera::SetZFar(float zFar) { m_zFar = zFar; }

  Matrix4 PerspectiveCamera::GetViewMatrix() const
  {
    return glm::lookAt(m_position, m_target, m_up);
  }

  Matrix4 PerspectiveCamera::GetProjectionMatrix() const
  {
    return glm::perspective(m_fovY, m_aspect, m_zNear, m_zFar);
  }

  Vector3 PerspectiveCamera::GetViewDirection()  const { return glm::normalize(m_target - m_position); }
  Vector3 PerspectiveCamera::GetTopDirection()   const { return glm::cross(GetViewDirection(), GetRightDirection()); }
  Vector3 PerspectiveCamera::GetRightDirection() const { return glm::cross(GetViewDirection(), glm::normalize(m_up)); }

  void PerspectiveCamera::SetPosition(const Vector3 & position) { m_position = position; }
  void PerspectiveCamera::LookAt(const Vector3 & target)        { m_target = target; }
  void PerspectiveCamera::SetUpDirection(const Vector3 & up)    { m_up = up; }
}
