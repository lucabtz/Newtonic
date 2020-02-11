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

#include <memory>
#include <unordered_map>

#include "assetprovider.h"

#include "core.h"
#include "util.h"

namespace Newtonic
{
  class AssetLoader
  {
  public:
    static void RegisterProvider(std::unique_ptr<IAssetProvider> provider);

    template<typename T>
    static std::shared_ptr<T> LoadAsset(AssetLoadingInformation *loadingInfo)
    {
      NW_WRAP_DEBUG(Core::GetCoreLogger().Debug(FormatString("Loading asset with strategy %d of type %d", loadingInfo->GetStrategy(), loadingInfo->GetType())));
      AssetType type = T::GetAssetType();

      const auto & found = s_providers.find(type);
      if (found != s_providers.end())
      {
        ASSERT_TRUE(found->second->GetProvidedType() == type);
        AssetProvider<T> * provider = static_cast<AssetProvider<T>*>(found->second.get());
        return provider->LoadAsset(loadingInfo);
      }

      return nullptr;
    }

  private:
    static std::unordered_map<AssetType, std::unique_ptr<IAssetProvider>> s_providers;
  };
}
