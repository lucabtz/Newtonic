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

#include "assetmanager.h"

#include "util.h"
#include "core.h"
#include "image.h"

namespace Newtonic
{
  std::vector<AssetResourceInfo> AssetManager::s_resourceInfos;
  std::unordered_map<std::string, unsigned int> AssetManager::s_idMap;
  std::unordered_map<unsigned int, std::shared_ptr<AssetInstance>> AssetManager::s_assets;

  unsigned int AssetManager::PushResourceInfo(const AssetResourceInfo & info)
  {
    unsigned int id = s_resourceInfos.size();
    s_resourceInfos.push_back(info);
    s_idMap[info.GetName()] = id;
    Core::GetCoreLogger().Debug(FormatString("Pushed new resource %s (%s) of type %i", info.GetName().c_str(), info.GetResourcePath().c_str(), info.GetType()));
    return id;
  }

  unsigned int AssetManager::GetIdFromName(const std::string & name)
  {
    ASSERT_TRUE(s_idMap.find(name) != s_idMap.end());
    return s_idMap[name];
  }

  void AssetManager::LoadAsset(unsigned int id)
  {
    ASSERT_TRUE(IdExists(id));

    AssetResourceInfo & info = s_resourceInfos[id];

    switch (info.GetType())
    {
    case AssetResourceType::TexturePNG:
      {
        Core::GetCoreLogger().Debug(FormatString("Loading asset %s, from %s", info.GetName().c_str(), info.GetResourcePath().c_str()));
        Image img = Image::LoadPNG(info.GetResourcePath().c_str());
        if (!img.IsValid())
        {
          Core::GetCoreLogger().Error(FormatString("Cannot load image from %s", info.GetResourcePath().c_str()));
          return;
        }
        Texture tex;
        tex.LoadFromImage(img);
        std::shared_ptr<AssetInstance> asset = std::make_shared<TextureAsset>(std::move(tex));
        s_assets[id] = asset;
        break;
      }
    case AssetResourceType::ShaderFilePair:
      {
        std::string res = info.GetResourcePath();
        ASSERT_TRUE(res.find(";") != std::string::npos);

        std::string vertexPath = res.substr(0, res.find(";"));
        std::string fragmentPath = res.substr(res.find(";")+1, res.size());

        Shader shader = Shader::CreateShader(ReadFile(vertexPath.c_str()).c_str(), ReadFile(fragmentPath.c_str()).c_str());
        std::shared_ptr<AssetInstance> asset = std::make_shared<ShaderAsset>(std::move(shader));
        s_assets[id] = asset;
        break;
      }
    default:
      {
        Core::GetCoreLogger().Error(FormatString("Invalid asset type for asset %s", info.GetName().c_str()));
        ASSERT_TRUE(false);
        break;
      }
    }

  }

  void AssetManager::LoadAsset(const std::string & name)
  {
    LoadAsset(GetIdFromName(name));
  }

  bool AssetManager::IsLoaded(unsigned int id)
  {
    return s_assets.find(id) != s_assets.end();
  }

  void AssetManager::GarbageCollect()
  {
    for (auto & pair : s_assets)
    {
      if (pair.second.use_count() == 1)
      {
        AssetResourceInfo & info = s_resourceInfos[pair.first];
        Core::GetCoreLogger().Debug(FormatString("Collecting %s no longer used", info.GetName().c_str()));
        pair.second.reset();
      }
    }
  }

  template<>
  std::shared_ptr<TextureAsset> AssetManager::GetAsset<TextureAsset>(unsigned int id)
  {
    ASSERT_TRUE(IdExists(id));

    if (!IsLoaded(id)) LoadAsset(id);
    ASSERT_TRUE(IsLoaded(id));
    ASSERT_TRUE(s_assets[id]->GetType() == AssetType::Texture);

    return std::dynamic_pointer_cast<TextureAsset>(s_assets[id]);
  }

  template<>
  std::shared_ptr<ShaderAsset> AssetManager::GetAsset<ShaderAsset>(unsigned int id)
  {
    ASSERT_TRUE(IdExists(id));

    if (!IsLoaded(id)) LoadAsset(id);
    ASSERT_TRUE(IsLoaded(id));
    ASSERT_TRUE(s_assets[id]->GetType() == AssetType::Shader);

    return std::dynamic_pointer_cast<ShaderAsset>(s_assets[id]);
  }
}
