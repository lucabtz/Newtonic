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

#include "serialization.h"
#include "math.h"

namespace Newtonic
{
  enum class UniformType : unsigned int
  {
    Invalid,
    Float, Float2, Float3, Float4,
    Mat4
  };

  class Uniform
  {
  public:
    Uniform();
    Uniform(UniformType type);
    Uniform(UniformType type, const std::string & symbol, const std::string & name);
    virtual ~Uniform();
    UniformType GetType() const;
    const std::string & GetName() const;
    const std::string & GetSymbol() const;
    virtual std::unique_ptr<Uniform> Clone() const;
  private:
    UniformType m_type;
    std::string m_symbol;
    std::string m_name;

    NW_PRIVATE_SERIALIZATION;
    template<typename Archive>
    void serialize(Archive & ar)
    {
      ar(
        cereal::make_nvp("Type", m_type),
        cereal::make_nvp("Name", m_name),
        cereal::make_nvp("Symbol", m_symbol)
      );
    }
  };

  class FloatUniform : public Uniform
  {
  public:
    FloatUniform();
    FloatUniform(float value, const std::string & symbol, const std::string & name);
    float GetValue() const;
    std::unique_ptr<Uniform> Clone() const override;

    void SetValue(float v);

  private:
    float m_value;

    NW_PRIVATE_SERIALIZATION;
    template<typename Archive>
    void serialize(Archive & ar)
    {
      ar(
        cereal::base_class<Uniform>(this),
        cereal::make_nvp("Value", m_value)
      );
    }
  };

  class Float2Uniform : public Uniform
  {
  public:
    Float2Uniform();
    Float2Uniform(const Vector2 & value, const std::string & symbol, const std::string & name);
    const Vector2 & GetValue() const;
    std::unique_ptr<Uniform> Clone() const override;

    void SetValue(const Vector2 & v);

  private:
    Vector2 m_value;

    NW_PRIVATE_SERIALIZATION;
    template<typename Archive>
    void serialize(Archive & ar)
    {
      ar(
        cereal::base_class<Uniform>(this),
        cereal::make_nvp("Value", m_value)
      );
    }
  };

  class Float3Uniform : public Uniform
  {
  public:
    Float3Uniform();
    Float3Uniform(const Vector3 & value, const std::string & symbol, const std::string & name);
    const Vector3 & GetValue() const;
    std::unique_ptr<Uniform> Clone() const override;

    void SetValue(const Vector3 & v);

  private:
    Vector3 m_value;

    NW_PRIVATE_SERIALIZATION;
    template<typename Archive>
    void serialize(Archive & ar)
    {
      ar(
        cereal::base_class<Uniform>(this),
        cereal::make_nvp("Value", m_value)
      );
    }
  };

  class Float4Uniform : public Uniform
  {
  public:
    Float4Uniform();
    Float4Uniform(const Vector4 & value, const std::string & symbol, const std::string & name);
    const Vector4 & GetValue() const;
    std::unique_ptr<Uniform> Clone() const override;

    void SetValue(const Vector4 & v);

  private:
    Vector4 m_value;

    NW_PRIVATE_SERIALIZATION;
    template<typename Archive>
    void serialize(Archive & ar)
    {
      ar(
        cereal::base_class<Uniform>(this),
        cereal::make_nvp("Value", m_value)
      );
    }
  };

  class Mat4Uniform : public Uniform
  {
  public:
    Mat4Uniform();
    Mat4Uniform(const Matrix4 & value, const std::string & symbol, const std::string & name);
    const Matrix4 & GetValue() const;
    std::unique_ptr<Uniform> Clone() const override;

    void SetValue(const Matrix4 & v);

  private:
    Matrix4 m_value;

    NW_PRIVATE_SERIALIZATION;
    template<typename Archive>
    void serialize(Archive & ar)
    {
      ar(
        cereal::base_class<Uniform>(this),
        cereal::make_nvp("Value", m_value)
      );
    }
  };
}

CEREAL_REGISTER_TYPE(Newtonic::FloatUniform)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Newtonic::Uniform, Newtonic::FloatUniform)

CEREAL_REGISTER_TYPE(Newtonic::Float2Uniform)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Newtonic::Uniform, Newtonic::Float2Uniform)

CEREAL_REGISTER_TYPE(Newtonic::Float3Uniform)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Newtonic::Uniform, Newtonic::Float3Uniform)

CEREAL_REGISTER_TYPE(Newtonic::Float4Uniform)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Newtonic::Uniform, Newtonic::Float4Uniform)

CEREAL_REGISTER_TYPE(Newtonic::Mat4Uniform)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Newtonic::Uniform, Newtonic::Mat4Uniform)
