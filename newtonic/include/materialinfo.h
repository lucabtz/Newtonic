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

#include "uniform.h"

namespace Newtonic
{
  class MaterialInfo
  {
  public:
    MaterialInfo();
    MaterialInfo(const std::string & shaderName);

    void PushUniform(std::unique_ptr<Uniform> uniform);

    const std::string & GetShaderName() const;

    const std::vector<std::unique_ptr<Uniform>> & GetUniforms() const;

  private:
    std::string m_shaderName;
    std::vector<std::unique_ptr<Uniform>> m_uniforms;

    NW_PRIVATE_SERIALIZATION;
    template<typename Archive>
    void serialize(Archive & ar)
    {
      ar(
        cereal::make_nvp("ShaderName", m_shaderName),
        cereal::make_nvp("Uniforms", m_uniforms)
      );
    }
  };
}
