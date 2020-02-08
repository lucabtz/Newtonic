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

#include "renderer/material.h"

#include "assetmanager.h"
#include "uniform.h"
#include "core.h"
#include "renderer/shader.h"

namespace Newtonic
{
  Material::Material() {}

  Material::Material(const MaterialInfo & info)
  {
    SetMaterialInfo(info);
  }

  void Material::SetMaterialInfo(const MaterialInfo & info)
  {
    for (const auto & uniform : info.GetUniforms())
    {
      m_uniforms[uniform->GetName()] = uniform->Clone();
    }
    m_shaderAsset = AssetManager::GetAsset<ShaderAsset>(info.GetShaderName());
  }

  void Material::SetFloat(const std::string & name, float v)
  {
    if (m_uniforms.find(name) != m_uniforms.end())
    {
      if (m_uniforms[name]->GetType() != UniformType::Float)
      {
        Core::GetCoreLogger().Error(FormatString("Uniform %s is not a float", name));
        ASSERT_TRUE(false);
      }
      dynamic_cast<FloatUniform*>(m_uniforms[name].get())->SetValue(v);
    }
  }

  void Material::SetVector2(const std::string & name, const Vector2 & v)
  {
    if (m_uniforms.find(name) != m_uniforms.end())
    {
      if (m_uniforms[name]->GetType() != UniformType::Float2)
      {
        Core::GetCoreLogger().Error(FormatString("Uniform %s is not a float2", name));
        ASSERT_TRUE(false);
      }
      dynamic_cast<Float2Uniform*>(m_uniforms[name].get())->SetValue(v);
    }
  }

  void Material::SetVector3(const std::string & name, const Vector3 & v)
  {
    if (m_uniforms.find(name) != m_uniforms.end())
    {
      if (m_uniforms[name]->GetType() != UniformType::Float3)
      {
        Core::GetCoreLogger().Error(FormatString("Uniform %s is not a float3", name));
        ASSERT_TRUE(false);
      }
      dynamic_cast<Float3Uniform*>(m_uniforms[name].get())->SetValue(v);
    }
  }

  void Material::SetVector4(const std::string & name, const Vector3 & v)
  {
    if (m_uniforms.find(name) != m_uniforms.end())
    {
      if (m_uniforms[name]->GetType() != UniformType::Float3)
      {
        Core::GetCoreLogger().Error(FormatString("Uniform %s is not a float3", name));
        ASSERT_TRUE(false);
      }
      dynamic_cast<Float3Uniform*>(m_uniforms[name].get())->SetValue(v);
    }
  }

  void Material::SetMatrix4(const std::string & name, const Matrix4 & v)
  {
    if (m_uniforms.find(name) != m_uniforms.end())
    {
      if (m_uniforms[name]->GetType() != UniformType::Mat4)
      {
        Core::GetCoreLogger().Error(FormatString("Uniform %s is not a mat4", name));
        ASSERT_TRUE(false);
      }
      dynamic_cast<Mat4Uniform*>(m_uniforms[name].get())->SetValue(v);
    }
  }

  void Material::Bind() const
  {
    Shader & shader = m_shaderAsset->GetShader();

    shader.Bind();
    for (const auto & uniformPair : m_uniforms)
    {
      auto & uniform = uniformPair.second;
      switch (uniform->GetType())
      {
      case UniformType::Invalid:
        {
          Core::GetCoreLogger().Debug(FormatString("Invalid uniform %s", uniform->GetName()));
          break;
        }
      case UniformType::Float:
        {
          shader.LoadFloat(uniform->GetSymbol(), dynamic_cast<FloatUniform*>(uniform.get())->GetValue());
          break;
        }
      case UniformType::Float2:
        {
          shader.LoadVector2(uniform->GetSymbol(), dynamic_cast<Float2Uniform*>(uniform.get())->GetValue());
          break;
        }
      case UniformType::Float3:
        {
          shader.LoadVector3(uniform->GetSymbol(), dynamic_cast<Float3Uniform*>(uniform.get())->GetValue());
          break;
        }
      case UniformType::Float4:
        {
          shader.LoadVector4(uniform->GetSymbol(), dynamic_cast<Float4Uniform*>(uniform.get())->GetValue());
          break;
        }
      case UniformType::Mat4:
        {
          shader.LoadMatrix4(uniform->GetSymbol(), dynamic_cast<Mat4Uniform*>(uniform.get())->GetValue());
          break;
        }
      }
    }
  }

  void Material::Unbind() const
  {
    Shader & shader = m_shaderAsset->GetShader();
    shader.Unbind();
  }

}
