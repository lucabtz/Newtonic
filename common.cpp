/*
 *   Newtonic - Graphics for Physics
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

#include "common.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace Newtonic
{

	const char *NewtonicException::what() const noexcept
	{
		return m_message.c_str();
	}

	std::string ReadFile(const char * path)
	{
		std::string result;
		std::ifstream fis(path, std::ios::in);
		if (fis.is_open())
		{
			std::stringstream sstream;
			sstream << fis.rdbuf();
			result = sstream.str();
			fis.close();
		}
		else
		{
			throw NewtonicException("Could not open file");
		}

		return result;
	}
}
