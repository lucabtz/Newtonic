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

	Mesh::Mesh(
		const std::vector<GLfloat> & positions,
		const std::vector<unsigned int> & indices) :
		m_positions(std::move(positions)),
		m_indices(std::move(indices))
	{
		m_vertCount = m_positions.size();
		m_indicesCount = m_indices.size();
		glGenVertexArrays(1, &m_vaoId);
		glBindVertexArray(m_vaoId);


		// positions VBO
		GLuint vboId;
		glGenBuffers(1, &vboId);
		m_vboIds.push_back(vboId);
		glBindBuffer(GL_ARRAY_BUFFER, vboId);
		glBufferData(GL_ARRAY_BUFFER, m_vertCount * sizeof(GLfloat), &m_positions[0], GL_STATIC_DRAW);

		// indices buffer
		GLuint indicesId;
		glGenBuffers(1, &indicesId);
		m_vboIds.push_back(indicesId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesCount * sizeof(GLuint), &m_indices[0], GL_STATIC_DRAW);
		m_indicesId = indicesId;
	}

	GLuint Mesh::GetPositionsVBO() const
	{
		return m_vboIds[0];
	}

	int Mesh::GetVertexCount() const
	{
		return m_vertCount;
	}

	void Mesh::BindMesh() const
	{
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, GetPositionsVBO());
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicesId);
	}

	void Mesh::RenderMesh() const
	{
		glDrawElements(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_INT, (void *)0);
	}

	void Mesh::UnbindMesh() const
	{
		glDisableVertexAttribArray(0);
	}

}
