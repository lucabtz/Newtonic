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

#include <exception>
#include <string>

#ifndef _COMMON_H
#define _COMMON_H

namespace Newtonic
{
	class NewtonicException : public std::exception
	{
		std::string m_message;

	public:
		inline NewtonicException(const char *message) :
			m_message(message)
		{}

		virtual const char *what() const noexcept;
	};


	std::string ReadFile(const char * path);

	struct Viewport
	{
		unsigned int width;
		unsigned int height;

		float GetScreenRatio() const
		{
			return (float)width / (float)height;
		}

		Viewport() : width(0), height(0) {}

		Viewport(int w, int h) : width(w), height(h) {}

		Viewport(const Viewport & other)
		{
			width = other.width;
			height = other.height;
		}

		Viewport & operator = (const Viewport & other)
		{
			width = other.width;
			height = other.height;
			return *this;
		}
	};

}

#endif // _COMMON_H
