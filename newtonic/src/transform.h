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
#include "serialization.h"

namespace Newtonic
{
  /**
   * A 3D object transform. Contains the object position, rotation and scale
   */
  class Transform
  {
  public:
    /**
     * Constructs an empty transform. position is the origin, no rotation and no scale
     */
    Transform();
    Transform(const Transform & other);
    Transform & operator =(const Transform & other);

    /**
     * Returns the transformation matrix
     */
    Matrix4 GetMatrix() const;

    /**
     * Returns the translation matrix
     */
    Matrix4 GetTranslationMatrix() const;

    /**
     * Returns the translation matrix
     */
    Matrix4 GetRotationMatrix() const;

    /**
     * Returns the scale matrix
     */
    Matrix4 GetScaleMatrix() const;

    /**
     * Returns the transform position
     */
    const Vector3 & GetPosition() const;

    /**
     * Returns the transform rotation
     */
    const Quaternion & GetRotation() const;

    /**
     * Returns the transform scale
     */
    const Vector3 & GetScale() const;

    /**
     * Returns the direction this transform is looking at.
     * Specifically it rotates the vector (0.0, 0.0, -1.0) by the transform rotation
     */
    Vector3 GetForwardDirection() const;

    /**
     * Returns the direction above the transform
     * Specifically it rotates the vector (0.0, 1.0, 0.0) by the transform rotation
     */
    Vector3 GetTopDirection() const;

    /**
     * Returns the direction right to the transform
     * Specifically it rotates the vector (1.0, 0.0, 0.0) by the transform rotation
     */
    Vector3 GetRightDirection() const;

    /**
     * Translates the transform by translation
     */
    void Translate(const Vector3 & translation);

    /**
     * Rotates the transform by rotation
     */
    void Rotate(const Quaternion & rotation);

    /**
     * Scales the transform by scale
     */
    void Scale(const Vector3 & scale);

    void SetPosition(const Vector3 & position);
    void SetRoation(const Quaternion & rotation);
    void SetScale(const Vector3 & scale);

  private:
    Vector3 m_position;
    Quaternion m_rotation;
    Vector3 m_scale;

    NW_PRIVATE_SERIALIZATION;
    template<typename Archive>
    void serialize(Archive & ar)
    {
      ar(
        cereal::make_nvp("XPosition", m_position.x),
        cereal::make_nvp("YPosition", m_position.y),
        cereal::make_nvp("ZPosition", m_position.z),
        cereal::make_nvp("XRotation", m_rotation.x),
        cereal::make_nvp("YRotation", m_rotation.y),
        cereal::make_nvp("ZRotation", m_rotation.z),
        cereal::make_nvp("WRotation", m_rotation.w),
        cereal::make_nvp("XScale", m_scale.x),
        cereal::make_nvp("YScale", m_scale.y),
        cereal::make_nvp("ZScale", m_scale.z)
      );
    }
  };
}
