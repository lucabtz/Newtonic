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

#include "serialization.h"

namespace Newtonic
{

  enum class AssetResourceType : unsigned int
  {
    Invalid = 0,
    TexturePNG = 1,
    // reserve ints for more texture assets
    MeshOBJ = 30,
    // reserve ints for more mesh assets
    Material = 50
  };

  class AssetResourceInfo
  {
  public:
    AssetResourceInfo();
    AssetResourceInfo(AssetResourceType type, const std::string & name, const std::string & resourcePath);
    AssetResourceInfo(const AssetResourceInfo & other);
    AssetResourceInfo & operator =(const AssetResourceInfo & other);

    AssetResourceType GetType() const;
    const std::string & GetName() const;
    const std::string & GetResourcePath() const;
  private:
    AssetResourceType m_type;
    std::string m_name;
    std::string m_resourcePath;

    NW_PRIVATE_SERIALIZATION;
    template<typename Archive>
    void serialize(Archive & ar)
    {
      ar(
        cereal::make_nvp("Type", m_type),
        cereal::make_nvp("Name", m_name),
        cereal::make_nvp("Path", m_resourcePath)
      );
    }
  };
}
