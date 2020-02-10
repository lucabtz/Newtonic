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

namespace Newtonic
{
  std::unordered_map<AssetType, std::unique_ptr<IAssetCache>> AssetManager::s_caches;
  std::unordered_map<std::string, std::unique_ptr<AssetLoadingInformation>> AssetManager::s_loadingInformation;

  void AssetManager::RegisterCache(std::unique_ptr<IAssetCache> cache)
  {
    NW_WRAP_DEBUG(Core::GetCoreLogger().Debug(FormatString("Registered cache for type %d", cache->GetCachedType())));
    s_caches[cache->GetCachedType()] = std::move(cache);
   }

  void AssetManager::RegisterAsset(const std::string & id, std::unique_ptr<AssetLoadingInformation> information)
  {
    NW_WRAP_DEBUG(Core::GetCoreLogger().Debug(FormatString("Registered asset %s of type %d with strategy %d", id.c_str(), information->GetType(), information->GetStrategy())));
    s_loadingInformation[id] = std::move(information);
  }

  void AssetManager::CollectGarbage()
  {
    for (auto & kv : s_caches)
    {
      kv.second->CollectGarbage();
    }
  }

}
