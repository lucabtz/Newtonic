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

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "serialization.h"

namespace Newtonic
{
  using Vector2 = glm::vec2;
  using Vector3 = glm::vec3;
  using Vector4 = glm::vec4;

  using Matrix2 = glm::mat2;
  using Matrix3 = glm::mat3;
  using Matrix4 = glm::mat4;

  using Quaternion = glm::quat;
}

namespace cereal
{
  template<typename Archive>
  void serialize(Archive & ar, Newtonic::Vector2 & vec)
  {
      ar(
        cereal::make_nvp("ValueX", vec.x),
        cereal::make_nvp("ValueY", vec.y)
      );
  }

  template<typename Archive>
  void serialize(Archive & ar, Newtonic::Vector3 & vec)
  {
      ar(
        cereal::make_nvp("ValueX", vec.x),
        cereal::make_nvp("ValueY", vec.y),
        cereal::make_nvp("ValueZ", vec.z)
      );
  }

  template<typename Archive>
  void serialize(Archive & ar, Newtonic::Vector4 & vec)
  {
      ar(
        cereal::make_nvp("ValueX", vec.x),
        cereal::make_nvp("ValueY", vec.y),
        cereal::make_nvp("ValueZ", vec.z),
        cereal::make_nvp("ValueW", vec.w)
      );
  }

  template<typename Archive>
  void serialize(Archive & ar, Newtonic::Matrix2 & mat)
  {
      ar(
        cereal::make_nvp("Value00", mat[0][0]),
        cereal::make_nvp("Value01", mat[0][1]),
        cereal::make_nvp("Value10", mat[1][0]),
        cereal::make_nvp("Value11", mat[1][1])
      );
  }

  template<typename Archive>
  void serialize(Archive & ar, Newtonic::Matrix3 & mat)
  {
      ar(
        cereal::make_nvp("Value00", mat[0][0]),
        cereal::make_nvp("Value01", mat[0][1]),
        cereal::make_nvp("Value02", mat[0][2]),
        cereal::make_nvp("Value10", mat[1][0]),
        cereal::make_nvp("Value11", mat[1][1]),
        cereal::make_nvp("Value12", mat[1][2]),
        cereal::make_nvp("Value20", mat[2][0]),
        cereal::make_nvp("Value21", mat[2][1]),
        cereal::make_nvp("Value22", mat[2][2])
      );
  }

  template<typename Archive>
  void serialize(Archive & ar, Newtonic::Matrix4 & mat)
  {
      ar(
        cereal::make_nvp("Value00", mat[0][0]),
        cereal::make_nvp("Value01", mat[0][1]),
        cereal::make_nvp("Value02", mat[0][2]),
        cereal::make_nvp("Value03", mat[0][3]),
        cereal::make_nvp("Value10", mat[1][0]),
        cereal::make_nvp("Value11", mat[1][1]),
        cereal::make_nvp("Value12", mat[1][2]),
        cereal::make_nvp("Value13", mat[1][3]),
        cereal::make_nvp("Value20", mat[2][0]),
        cereal::make_nvp("Value21", mat[2][1]),
        cereal::make_nvp("Value22", mat[2][2]),
        cereal::make_nvp("Value23", mat[2][3]),
        cereal::make_nvp("Value30", mat[3][0]),
        cereal::make_nvp("Value31", mat[3][1]),
        cereal::make_nvp("Value32", mat[3][2]),
        cereal::make_nvp("Value33", mat[3][3])
      );
  }

  template<typename Archive>
  void serialize(Archive & ar, Newtonic::Quaternion & quat)
  {
      ar(
        cereal::make_nvp("ValueX", quat.x),
        cereal::make_nvp("ValueY", quat.y),
        cereal::make_nvp("ValueZ", quat.z),
        cereal::make_nvp("ValueW", quat.w)
      );
  }

}
