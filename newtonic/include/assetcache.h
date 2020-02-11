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
      if (!IsAssetCached(id))
      {
        m_cache[id] = std::move(asset);
      }
      else
      {
        NW_WRAP_DEBUG(Core::GetCoreLogger().Debug(FormatString("Trying to cache already cached %s", id.c_str())));
      }
    }

    bool IsAssetCached(const std::string & id) const
    {
      const auto & found = m_cache.find(id);
      return (found != m_cache.end() && found->second); // here checking found->second != nullptr should not be necessary but just in case
                                                        // the code that is using the asset calls reset on shared_ptr
                                                        // this check prevents breaking everything
    }

    std::shared_ptr<T> GetAsset(const std::string & id) const
    {
      const auto & found = m_cache.find(id);
      if (found != m_cache.end())
      {
        return (*found).second;
      }
      return nullptr;
    }

    void CollectGarbage() override
    {
      for (auto iter = m_cache.begin(); iter != m_cache.end();)
      {
        if (iter->second.use_count() <= 1 || iter->second == nullptr) // the nullptr check is probably redundant but just in case
        {
          // in this case the only reference left is the cache reference
          // we can free the asset from the cache
          NW_WRAP_DEBUG(Core::GetCoreLogger().Debug(FormatString("Collecting asset %s of type %i", iter->first.c_str(), T::GetAssetType())));
          iter = m_cache.erase(iter);
        }
        else
        {
          ++iter;
        }
      }
    }

  private:
    std::unordered_map<std::string, std::shared_ptr<T>> m_cache;
  };
}
