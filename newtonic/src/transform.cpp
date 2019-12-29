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

#include "transform.h"

namespace Newtonic
{

  Vector3 Transform::GetPosition() { return m_position; }
  Vector3 Transform::GetRotationEulerAngles() { return glm::eulerAngles(m_rotation); }
  Vector3 Transform::GetScale() { return m_scale; }

  void Transform::SetPosition(const Vector3 & newPosition) { m_position = newPosition; }
  void Transform::SetRotationEulerAngles(const Vector3 & newRotation) { m_rotation = Quaternion(newRotation); }
  void Transform::SetScale(const Vector3 & newScale) { m_scale = newScale; }

  Matrix4 Transform::GetTranslationMatrix() { return glm::translate(Matrix4(1.0), m_position); }
  Matrix4 Transform::GetRotationMatrix() { return glm::toMat4(m_rotation); }
  Matrix4 Transform::GetScaleMatrix(){ return glm::scale(Matrix4(1.0), m_scale); }

  Vector3 Transform::GetForwardDirection()
  {
    auto rotation = GetRotationMatrix();
    auto res = rotation * Vector4(0.0, 0.0, -1.0, 0.0);
    return Vector3(res.x, res.y, res.z);
  }

  Vector3 Transform::GetRightDirection()
  {
    auto rotation = GetRotationMatrix();
    auto res = rotation * Vector4(1.0, 0.0, 0.0, 0.0);
    return Vector3(res.x, res.y, res.z);
  }

  Vector3 Transform::GetUpDirection()
  {
    auto rotation = GetRotationMatrix();
    auto res = rotation * Vector4(0.0, 1.0, 0.0, 0.0);
    return Vector3(res.x, res.y, res.z);
  }

  Matrix4 Transform::GetTransformationMatrix()
  {
    Matrix4 scaleMatrix = GetScaleMatrix();
    Matrix4 rotationMatrix = GetRotationMatrix();
    Matrix4 translationMatrix = GetTranslationMatrix();
    return translationMatrix * rotationMatrix * scaleMatrix;
  }

}
