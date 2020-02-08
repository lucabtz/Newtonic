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

#include "assetresourceinfo.h"
#include "assetinstance.h"

#include <vector>
#include <unordered_map>
#include <string>
#include <memory>

namespace Newtonic
{
  class AssetManager
  {
  public:
    static unsigned int PushResourceInfo(const AssetResourceInfo & info);

    static unsigned int GetIdFromName(const std::string & name);

    static void LoadAsset(unsigned int id);
    static void LoadAsset(const std::string & name);

    static bool IsLoaded(unsigned int id);

    template<typename T>
    static std::shared_ptr<T> GetAsset(unsigned int id);

    template<typename T>
    static std::shared_ptr<T> GetAsset(const std::string & name)
    {
      return GetAsset<T>(GetIdFromName(name));
    }

    static void GarbageCollect();

  private:
    static std::vector<AssetResourceInfo> s_resourceInfos;
    static std::unordered_map<std::string, unsigned int> s_idMap;
    static std::unordered_map<unsigned int, std::shared_ptr<AssetInstance>> s_assets;

    static bool IdExists(unsigned int id) { return id < s_resourceInfos.size(); }
  };
}
