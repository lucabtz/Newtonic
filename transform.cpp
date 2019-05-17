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

#include "transform.h"

namespace Newtonic
{

  glm::vec3 Transform::GetPosition() { return m_position; }
  glm::vec3 Transform::GetRotationEulerAngles() { return glm::eulerAngles(m_rotation); }
  glm::vec3 Transform::GetScale() { return m_scale; }

  void Transform::SetPosition(const glm::vec3 & newPosition) { m_position = newPosition; }
  void Transform::SetRotationEulerAngles(const glm::vec3 & newRotation) { m_rotation = glm::quat(newRotation); }
  void Transform::SetScale(const glm::vec3 & newScale) { m_scale = newScale; }

  glm::mat4 Transform::GetTranslationMatrix() { return glm::translate(glm::mat4(1.0), m_position); }
  glm::mat4 Transform::GetRotationMatrix() { return glm::toMat4(m_rotation); }
  glm::mat4 Transform::GetScaleMatrix(){ return glm::scale(glm::mat4(1.0), m_scale); }

  glm::mat4 Transform::GetTransformationMatrix()
  {
    glm::mat4 scaleMatrix = GetScaleMatrix();
    glm::mat4 rotationMatrix = GetRotationMatrix();
    glm::mat4 translationMatrix = GetTranslationMatrix();
    return translationMatrix * rotationMatrix * scaleMatrix;
  }

}
