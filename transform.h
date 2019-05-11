/*
 *   Newtonic - Graphics for Physics
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

#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Newtonic
{
  class Transform
  {
    glm::vec3 m_position;
    glm::quat m_rotation;
    glm::vec3 m_scale;

  public:
    Transform() :
      m_position(0.0, 0.0, 0.0),
      m_rotation(0.0, 1.0, 0.0, 0.0),
      m_scale(1.0, 1.0, 1.0)
    {}
    glm::vec3 GetPosition();
    glm::vec3 GetRotationEulerAngles();
    glm::vec3 GetScale();

    void SetPosition(const glm::vec3 & newPosition);
    void SetRotationEulerAngles(const glm::vec3 & newRotation);
    void SetScale(const glm::vec3 & newScale);

    glm::mat4 GetTransformationMatrix();
  };
}

#endif // _TRANFORM_H
