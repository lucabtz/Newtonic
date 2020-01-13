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

#include "assetresourceinfo.h"

namespace Newtonic
{
  AssetResourceInfo::AssetResourceInfo() : AssetResourceInfo(AssetResourceType::Invalid, "", "") {}

  AssetResourceInfo::AssetResourceInfo(AssetResourceType type, const std::string & name, const std::string & resourcePath)
    : m_type(type),
      m_name(name),
      m_resourcePath(resourcePath)
  {}

  AssetResourceInfo::AssetResourceInfo(const AssetResourceInfo & other)
    : m_type(other.m_type),
      m_name(other.m_name),
      m_resourcePath(other.m_resourcePath)
  {}

  AssetResourceInfo & AssetResourceInfo::operator =(const AssetResourceInfo & other)
  {
    m_type = other.m_type;
    m_name = other.m_name;
    m_resourcePath = other.m_resourcePath;
    return *this;
  }

  AssetResourceType AssetResourceInfo::GetType() const { return m_type; }
  const std::string & AssetResourceInfo::GetName() const { return m_name; }
  const std::string & AssetResourceInfo::GetResourcePath() const { return m_resourcePath; }

}
