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

namespace Newtonic
{
  enum class AssetLoadingStrategy : unsigned int
  {
    FileSystem,
    Shader
  };

  struct AssetLoadingInformation
  {
    AssetLoadingInformation(AssetLoadingStrategy s, AssetType t) : strategy(s), type(t) {}
    AssetLoadingStrategy strategy;
    AssetType type;

    virtual AssetLoadingStrategy GetStrategy() { return strategy; }
    virtual AssetType GetType() { return type; }
  };

  struct FileSystemLoadingInformation : public AssetLoadingInformation
  {
    FileSystemLoadingInformation() : AssetLoadingInformation(AssetLoadingStrategy::FileSystem, AssetType::Undefined) {}
    FileSystemLoadingInformation(AssetType type, const std::string & p) : AssetLoadingInformation(AssetLoadingStrategy::FileSystem, type), path(p) {}
    std::string path;
  };

  struct ShaderLoadingInformation : public AssetLoadingInformation
  {
    ShaderLoadingInformation() : AssetLoadingInformation(AssetLoadingStrategy::Shader, AssetType::Undefined) {}
    ShaderLoadingInformation(AssetType type, const std::string & p1, const std::string & p2) : AssetLoadingInformation(AssetLoadingStrategy::Shader, type), vertexPath(p1), fragmentPath(p2) {}
    std::string vertexPath;
    std::string fragmentPath;
  };
}
