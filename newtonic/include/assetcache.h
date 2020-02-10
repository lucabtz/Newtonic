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

#include <string>
#include <unordered_map>

#include "core.h"
#include "util.h"

namespace Newtonic
{
  class IAssetCache
  {
  public:
    virtual AssetType GetCachedType() = 0;
    virtual void CollectGarbage() = 0;
  };

  template<typename T>
  class AssetCache : public IAssetCache
  {
  public:
    AssetType GetCachedType() override
    {
      return T::GetAssetType();
    }

    void CacheAsset(const std::string & id, std::shared_ptr<T> asset)
    {
      m_cache[id] = asset;
    }

    bool IsAssetCached(const std::string & id)
    {
      return (m_cache.find(id) != m_cache.end() && m_cache[id]);
    }

    std::shared_ptr<T> GetAsset(const std::string & id)
    {
      return m_cache[id];
    }

    void CollectGarbage() override
    {
      for (auto & kv : m_cache)
      {
        if (kv.second.use_count() == 1)
        {
          // in this case the only reference left is the cache reference
          // we can free the asset from the cache
          NW_WRAP_DEBUG(Core::GetCoreLogger().Debug(FormatString("Collecting asset %s of type %i", kv.first.c_str(), T::GetAssetType())));
          kv.second.reset();
        }
      }
    }

  private:
    std::unordered_map<std::string, std::shared_ptr<T>> m_cache;
  };
}
