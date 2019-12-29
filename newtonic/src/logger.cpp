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

#include "logger.h"

#include <iostream>

namespace Newtonic
{
  Logger::Logger() : m_name("LOG") {}
  Logger::Logger(const std::string & name) : m_name(name) {}
  Logger::Logger(const Logger & other) : m_name(other.m_name) {}
  Logger & Logger::operator=(const Logger & other) { m_name = other.m_name; return *this; }

  void Logger::Error(const std::string & message) const
  {
    std::cerr << "[" << m_name << "] ERROR: " << message << std::endl;
  }

  void Logger::Warning(const std::string & message) const
  {
    std::cout << "[" << m_name << "] WARN: " << message << std::endl;
  }

  void Logger::Info(const std::string & message) const
  {
    std::cout << "[" << m_name << "] INFO: " << message << std::endl;
  }

  void Logger::Debug(const std::string & message) const
  {
    std::cout << "[" << m_name << "] DEBUG: " << message << std::endl;
  }

}
