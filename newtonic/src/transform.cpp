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
  Transform::Transform() : m_position(0,0,0), m_rotation(1,0,0,0), m_scale(1,1,1) {}
  Transform::Transform(const Transform & other) : m_position(other.m_position), m_rotation(other.m_rotation), m_scale(other.m_scale) {}
  Transform & Transform::operator =(const Transform & other)
  {
    m_position = other.m_position;
    m_rotation = other.m_rotation;
    m_scale = other.m_scale;
    return *this;
  }

  Matrix4 Transform::GetMatrix() const
  {
    Matrix4 scaleMatrix = GetScaleMatrix();
    Matrix4 rotationMatrix = GetRotationMatrix();
    Matrix4 translationMatrix = GetTranslationMatrix();
    return translationMatrix * rotationMatrix * scaleMatrix;
  }

  Matrix4 Transform::GetTranslationMatrix() const
  {
    return glm::translate(Matrix4(1.0), m_position);
  }

  Matrix4 Transform::GetRotationMatrix() const
  {
    return glm::toMat4(m_rotation);
  }

  Matrix4 Transform::GetScaleMatrix() const
  {
    return glm::scale(Matrix4(1.0), m_scale);
  }

  const Vector3 & Transform::GetPosition() const    { return m_position; }
  const Quaternion & Transform::GetRotation() const { return m_rotation; }
  const Vector3 & Transform::GetScale() const       { return m_scale; }

  Vector3 Transform::GetForwardDirection() const
  {
    const Matrix4 & rot = GetRotationMatrix();
    Vector4 result = rot * Vector4(0.0, 0.0, -1.0, 0.0);
    return Vector3(result.x, result.y, result.z);
  }

  Vector3 Transform::GetTopDirection() const
  {
    const Matrix4 & rot = GetRotationMatrix();
    Vector4 result = rot * Vector4(0.0, 1.0, 0.0, 0.0);
    return Vector3(result.x, result.y, result.z);
  }

  Vector3 Transform::GetRightDirection() const
  {
    const Matrix4 & rot = GetRotationMatrix();
    Vector4 result = rot * Vector4(1.0, 0.0, 0.0, 0.0);
    return Vector3(result.x, result.y, result.z);
  }


  void Transform::Translate(const Vector3 & translation)
  {
    m_position += translation;
  }

  void Transform::Rotate(const Quaternion & rotation)
  {
    m_rotation *= rotation;
  }

  void Transform::Scale(const Vector3 & scale)
  {
    m_scale = Vector3(m_scale.x * scale.x, m_scale.y * scale.y, m_scale.z * scale.z);
  }

  void Transform::SetPosition(const Vector3 & position)
  {
    m_position = position;
  }

  void Transform::SetRoation(const Quaternion & rotation)
  {
    m_rotation = rotation;
  }

  void Transform::SetScale(const Vector3 & scale)
  {
    m_scale = scale;
  }
}
