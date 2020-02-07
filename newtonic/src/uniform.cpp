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

#include "uniform.h"

namespace Newtonic
{
  Uniform::Uniform() : m_type(UniformType::Invalid) {}
  Uniform::Uniform(UniformType type) : m_type(type), m_symbol(""), m_name("") {}
  Uniform::Uniform(UniformType type, const std::string & symbol, const std::string & name) : m_type(type), m_symbol(symbol), m_name(name) {}
  Uniform::~Uniform() {}
  UniformType Uniform::GetType() const { return m_type; }
  const std::string & Uniform::GetName() const { return m_name; }
  const std::string & Uniform::GetSymbol() const { return m_symbol; }
  std::unique_ptr<Uniform> Uniform::Clone() const { return std::make_unique<Uniform>(m_type, m_symbol, m_name); }

  FloatUniform::FloatUniform() : Uniform(UniformType::Float), m_value(0.0f) {}
  FloatUniform::FloatUniform(float value, const std::string & symbol, const std::string & name) : Uniform(UniformType::Float, symbol, name), m_value(value) {}
  float FloatUniform::GetValue() const { return m_value; }
  std::unique_ptr<Uniform> FloatUniform::Clone() const { return std::make_unique<FloatUniform>(m_value, GetSymbol(), GetName()); }
  void FloatUniform::SetValue(float v) { m_value = v; }

  Float2Uniform::Float2Uniform() : Uniform(UniformType::Float2), m_value(0.0f, 0.0f) {}
  Float2Uniform::Float2Uniform(const Vector2 & value, const std::string & symbol, const std::string & name) : Uniform(UniformType::Float2, symbol, name), m_value(value) {}
  const Vector2 & Float2Uniform::GetValue() const { return m_value; }
  std::unique_ptr<Uniform> Float2Uniform::Clone() const { return std::make_unique<Float2Uniform>(m_value, GetSymbol(), GetName()); }
  void Float2Uniform::SetValue(const Vector2 & v) { m_value = v; }

  Float3Uniform::Float3Uniform() : Uniform(UniformType::Float3), m_value(0.0f, 0.0f, 0.0f) {}
  Float3Uniform::Float3Uniform(const Vector3 & value, const std::string & symbol, const std::string & name) : Uniform(UniformType::Float3, symbol, name), m_value(value) {}
  const Vector3 & Float3Uniform::GetValue() const { return m_value; }
  std::unique_ptr<Uniform> Float3Uniform::Clone() const { return std::make_unique<Float3Uniform>(m_value, GetSymbol(), GetName()); }
  void Float3Uniform::SetValue(const Vector3 & v) { m_value = v; }

  Float4Uniform::Float4Uniform() : Uniform(UniformType::Float4), m_value(0.0f, 0.0f, 0.0f, 0.0f) {}
  Float4Uniform::Float4Uniform(const Vector4 & value, const std::string & symbol, const std::string & name) : Uniform(UniformType::Float4, symbol, name), m_value(value) {}
  const Vector4 & Float4Uniform::GetValue() const { return m_value; }
  std::unique_ptr<Uniform> Float4Uniform::Clone() const { return std::make_unique<Float4Uniform>(m_value, GetSymbol(), GetName()); }
  void Float4Uniform::SetValue(const Vector4 & v) { m_value = v; }

  Mat4Uniform::Mat4Uniform() : Uniform(UniformType::Mat4), m_value() {}
  Mat4Uniform::Mat4Uniform(const Matrix4 & value, const std::string & symbol, const std::string & name) : Uniform(UniformType::Mat4, symbol, name), m_value(value) {}
  const Matrix4 & Mat4Uniform::GetValue() const { return m_value; }
  std::unique_ptr<Uniform> Mat4Uniform::Clone() const { return std::make_unique<Mat4Uniform>(m_value, GetSymbol(), GetName()); }
  void Mat4Uniform::SetValue(const Matrix4 & v) { m_value = v; }

}
