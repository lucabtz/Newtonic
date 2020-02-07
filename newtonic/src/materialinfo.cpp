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

#include "materialinfo.h"

#include <utility>

namespace Newtonic
{
  MaterialInfo::MaterialInfo() : m_shaderName("") {}
  MaterialInfo::MaterialInfo(const std::string & shaderName) : m_shaderName(shaderName) {}

  void MaterialInfo::PushUniform(std::unique_ptr<Uniform> uniform)
  {
    m_uniforms.push_back(std::move(uniform));
  }
  
  const std::string & MaterialInfo::GetShaderName() const
  {
    return m_shaderName;
  }

  const std::vector<std::unique_ptr<Uniform>> & MaterialInfo::GetUniforms() const
  {
    return m_uniforms;
  }
}
