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

#include "asset.h"
#include <string>

#include "assetloadinginformation.h"

#include "image.h"
#include "renderer/texture.h"
#include "renderer/shader.h"

namespace Newtonic
{

  class IAssetProvider
  {
  public:
    virtual AssetType GetProvidedType() = 0;
  };

  template<typename T>
  class AssetProvider : public IAssetProvider {};

  template<>
  class AssetProvider<Texture> : public IAssetProvider
  {
  public:
    AssetType GetProvidedType() override
    {
      return Texture::GetAssetType();
    }

    std::shared_ptr<Texture> LoadAsset(AssetLoadingInformation *loadingInfo)
    {
      switch(loadingInfo->strategy)
      {
        case AssetLoadingStrategy::FileSystem:
        {
          FileSystemLoadingInformation *fsinfo = static_cast<FileSystemLoadingInformation*>(loadingInfo);
          ASSERT_TRUE(fsinfo != nullptr);
          Image img = Image::LoadPNG(fsinfo->path.c_str());
          if (!img.IsValid())
          {
            Core::GetCoreLogger().Error(FormatString("File %s not found", fsinfo->path.c_str()));
            ASSERT_TRUE(false);
          }
          std::shared_ptr<Texture> tex = std::make_shared<Texture>();
          tex->LoadFromImage(img);
          return tex;
        }
      default:
        Core::GetCoreLogger().Error("Invalid loading strategy for type texture");
      }

      ASSERT_TRUE(false);
      return nullptr;
    }
  };

  template<>
  class AssetProvider<Shader> : public IAssetProvider
  {
  public:
    AssetType GetProvidedType() override
    {
      return Shader::GetAssetType();
    }

    std::shared_ptr<Shader> LoadAsset(AssetLoadingInformation *loadingInfo)
    {
      switch(loadingInfo->strategy)
      {
      case AssetLoadingStrategy::Shader:
        {
          ShaderLoadingInformation *sinfo = static_cast<ShaderLoadingInformation*>(loadingInfo);
          ASSERT_TRUE(sinfo != nullptr);
          std::shared_ptr<Shader> shader = Shader::CreateShader(ReadFile(sinfo->vertexPath).c_str(), ReadFile(sinfo->fragmentPath).c_str());
          return shader;
        }
      default:
        Core::GetCoreLogger().Error("Invalid loading strategy for type shader");
      }

      ASSERT_TRUE(false);
      return nullptr;
    }
  };
}
