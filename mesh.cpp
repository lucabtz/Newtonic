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

#include "mesh.h"

namespace Newtonic
{

	Mesh::Mesh(const Mesh && other) :
		m_vaoId(other.m_vaoId),
		m_vboIds(std::move(other.m_vboIds)),
		m_positions(std::move(other.m_positions)),
		m_vertCount(other.m_vertCount)
	{}

	Mesh::Mesh(const std::vector<GLfloat> & positions) :
		m_positions(std::move(positions))
	{
		m_vertCount = m_positions.size();
		glGenVertexArrays(1, &m_vaoId);
		glBindVertexArray(m_vaoId);

		GLuint vboId;
		glGenBuffers(1, &vboId);
		m_vboIds.push_back(vboId);
		glBindBuffer(GL_ARRAY_BUFFER, vboId);
		glBufferData(GL_ARRAY_BUFFER, m_vertCount * sizeof(GLuint), &m_positions[0], GL_STATIC_DRAW);
	}

	GLuint Mesh::GetPositionsVBO() const
	{
		return m_vboIds[0];
	}

	int Mesh::GetVertexCount() const
	{
		return m_vertCount;
	}

}
