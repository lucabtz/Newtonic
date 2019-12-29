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
#include <stdexcept>
#include <memory>
#include <assert.h>

#define ASSERT_TRUE(x) assert(x)
#define ASSERT_FALSE(x) assert(!(x))

#define NW_WRAP_DEBUG(x) x

namespace Newtonic
{
  std::string ReadFile(const char * path);

  template<typename... Args>
  std::string FormatString(const std::string & format, Args ... args)
  {
    size_t size = std::snprintf(nullptr, 0, format.c_str(), args...);
    if (size <= 0) throw std::runtime_error("Error formatting string");
    std::unique_ptr<char[]> buf(new char[size+1]);
    std::snprintf(buf.get(), size+1, format.c_str(), args...);
    return std::string(buf.get(), size);
  }
}
