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

  Material::Material(const MaterialDefinition & info)
  {
    Instantiate(info);
  }

  void Material::Instantiate(const MaterialDefinition & info)
  {
    m_shader = info.GetShader();
    for (const auto & uniform : info.GetUniforms())
    {
      m_uniforms[uniform->GetName()] = uniform->Clone();
      if(uniform->GetType() == UniformType::Texture)
      {
        const std::string & texName = dynamic_cast<TextureUniform*>(uniform.get())->GetValue();
        m_textures[texName] = AssetManager::GetAsset<Texture>(texName);
      }
    }
  }

  void Material::SetFloat(const std::string & name, float v)
  {
    if (m_uniforms.find(name) != m_uniforms.end())
    {
      if (m_uniforms[name]->GetType() != UniformType::Float)
      {
        Core::GetCoreLogger().Error(FormatString("Uniform %s is not a float", name.c_str()));
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
        Core::GetCoreLogger().Error(FormatString("Uniform %s is not a float2", name.c_str()));
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
        Core::GetCoreLogger().Error(FormatString("Uniform %s is not a float3", name.c_str()));
        ASSERT_TRUE(false);
      }
      dynamic_cast<Float3Uniform*>(m_uniforms[name].get())->SetValue(v);
    }
  }

  void Material::SetVector4(const std::string & name, const Vector4 & v)
  {
    if (m_uniforms.find(name) != m_uniforms.end())
    {
      if (m_uniforms[name]->GetType() != UniformType::Float4)
      {
        Core::GetCoreLogger().Error(FormatString("Uniform %s is not a float4", name.c_str()));
        ASSERT_TRUE(false);
      }
      dynamic_cast<Float4Uniform*>(m_uniforms[name].get())->SetValue(v);
    }
  }

  void Material::SetMatrix4(const std::string & name, const Matrix4 & v)
  {
    if (m_uniforms.find(name) != m_uniforms.end())
    {
      if (m_uniforms[name]->GetType() != UniformType::Mat4)
      {
        Core::GetCoreLogger().Error(FormatString("Uniform %s is not a mat4", name.c_str()));
        ASSERT_TRUE(false);
      }
      dynamic_cast<Mat4Uniform*>(m_uniforms[name].get())->SetValue(v);
    }
  }

  void Material::SetTexture(const std::string & name, const std::string & v)
  {
    if (m_uniforms.find(name) != m_uniforms.end())
    {
      if (m_uniforms[name]->GetType() != UniformType::Texture)
      {
        Core::GetCoreLogger().Error(FormatString("Uniform %s is not a texture", name.c_str()));
        ASSERT_TRUE(false);
      }
      dynamic_cast<TextureUniform*>(m_uniforms[name].get())->SetValue(v);
      m_textures[v] = AssetManager::GetAsset<Texture>(v);
    }
  }

  void Material::Bind() const
  {
    ASSERT_TRUE(m_shader != nullptr);
    Shader & shader = *m_shader;

    shader.Bind();
    int texSlot = 0;
    for (const auto & uniformPair : m_uniforms)
    {
      auto & uniform = uniformPair.second;
      switch (uniform->GetType())
      {
      case UniformType::Invalid:
        {
          Core::GetCoreLogger().Debug(FormatString("Invalid uniform %s", uniform->GetName().c_str()));
          break;
        }
      case UniformType::Float:
        {
          shader.LoadFloat(uniform->GetSymbol(), static_cast<FloatUniform*>(uniform.get())->GetValue());
          break;
        }
      case UniformType::Float2:
        {
          shader.LoadVector2(uniform->GetSymbol(), static_cast<Float2Uniform*>(uniform.get())->GetValue());
          break;
        }
      case UniformType::Float3:
        {
          shader.LoadVector3(uniform->GetSymbol(), static_cast<Float3Uniform*>(uniform.get())->GetValue());
          break;
        }
      case UniformType::Float4:
        {
          shader.LoadVector4(uniform->GetSymbol(), static_cast<Float4Uniform*>(uniform.get())->GetValue());
          break;
        }
      case UniformType::Mat4:
        {
          shader.LoadMatrix4(uniform->GetSymbol(), static_cast<Mat4Uniform*>(uniform.get())->GetValue());
          break;
        }
      case UniformType::Texture:
        {
          const std::string & texName = static_cast<TextureUniform*>(uniform.get())->GetValue();
          std::shared_ptr<Texture> & tex = m_textures.find(texName)->second;
          tex->Bind(texSlot);
          shader.LoadUniform1i(uniform->GetSymbol(), texSlot);
          texSlot++;
          break;
        }
      }
    }
  }

  void Material::Unbind() const
  {
    m_shader->Unbind();
  }

}
