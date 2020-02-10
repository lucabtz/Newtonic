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
#include "assetcache.h"
#include "assetloader.h"
#include "assetloadinginformation.h"

namespace Newtonic
{
  class AssetManager
  {
  public:
    static void RegisterCache(std::unique_ptr<IAssetCache> cache);
    static void RegisterAsset(const std::string & id, std::unique_ptr<AssetLoadingInformation> information);

    template<typename T>
    static std::shared_ptr<T> GetAsset(const std::string & id)
    {
      AssetType type = T::GetAssetType();
      if (s_caches.find(type) != s_caches.end())
      {
        ASSERT_TRUE(s_caches[type]->GetCachedType() == type);
        AssetCache<T> *cache = dynamic_cast<AssetCache<T>*>(s_caches[type].get());
        ASSERT_TRUE(cache != nullptr);
        if (cache->IsAssetCached(id))
        {
          return cache->GetAsset(id);
        }
        ASSERT_TRUE(s_loadingInformation.find(id) != s_loadingInformation.end());
        ASSERT_TRUE(s_loadingInformation[id]->type == type);
        std::shared_ptr<T> asset = AssetLoader::LoadAsset<T>(s_loadingInformation[id].get());
        cache->CacheAsset(id, asset);
        return asset;
      }
      NW_WRAP_DEBUG(Core::GetCoreLogger().Debug(FormatString("Cache for type %d not registered", type)));
      ASSERT_TRUE(s_loadingInformation.find(id) != s_loadingInformation.end());
      return AssetLoader::LoadAsset<T>(s_loadingInformation[id].get());
    }

    static void CollectGarbage();
  private:
    static std::unordered_map<AssetType, std::unique_ptr<IAssetCache>> s_caches;
    static std::unordered_map<std::string, std::unique_ptr<AssetLoadingInformation>> s_loadingInformation;
  };
}
