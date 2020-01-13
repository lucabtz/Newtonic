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

#include "renderer/texture.h"
#include "renderer/mesh.h"
#include "renderer/shader.h"

namespace Newtonic
{
  enum class AssetType : unsigned int
  {
    Texture,
    Mesh,
    Material,
    Shader
  };

  class AssetInstance
  {
  public:
    AssetInstance(AssetType type);
    virtual ~AssetInstance();
    AssetType GetType() const;

  private:
    AssetType m_type;
  };

  class TextureAsset : public AssetInstance
  {
  public:
    TextureAsset(Texture texture);

    Texture & GetTexture();
  private:
    Texture m_texture;
  };

  class MeshAsset : public AssetInstance
  {
  public:
    MeshAsset(Mesh mesh);

    Mesh & GetMesh();
  private:
    Mesh m_mesh;
  };

  class ShaderAsset : public AssetInstance
  {
  public:
    ShaderAsset(Shader shader);

    Shader & GetShader();
  private:
    Shader m_shader;
  };
}
