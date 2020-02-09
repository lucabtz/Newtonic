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

#include "materialdefinition.h"
#include "util.h"

#include "json.h"

#include <utility>

namespace Newtonic
{
  MaterialDefinition::MaterialDefinition() : m_shaderName("") {}
  MaterialDefinition::MaterialDefinition(const std::string & shaderName) : m_shaderName(shaderName) {}

  MaterialDefinition::MaterialDefinition(MaterialDefinition && other) : m_shaderName(std::move(other.m_shaderName)), m_uniforms(std::move(other.m_uniforms))
  {}

  MaterialDefinition & MaterialDefinition::operator =(MaterialDefinition && other)
  {
    m_shaderName = std::move(other.m_shaderName);
    m_uniforms = std::move(other.m_uniforms);
    return *this;
  }

  void MaterialDefinition::PushUniform(std::unique_ptr<Uniform> uniform)
  {
    m_uniforms.push_back(std::move(uniform));
  }

  const std::string & MaterialDefinition::GetShaderName() const
  {
    return m_shaderName;
  }

  const std::vector<std::unique_ptr<Uniform>> & MaterialDefinition::GetUniforms() const
  {
    return m_uniforms;
  }
}
