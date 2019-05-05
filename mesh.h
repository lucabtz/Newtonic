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

#ifndef _MESH_H
#define _MESH_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

namespace Newtonic
{
	class Mesh
	{
		GLuint m_vaoId;
		std::vector<GLuint> m_vboIds;
		std::vector<GLfloat> m_positions;
		int m_vertCount;

	public:
		Mesh(const std::vector<GLfloat> & positions);
		Mesh(const Mesh && other);

		int GetVertexCount() const;

		GLuint GetPositionsVBO() const;

		void BindMesh() const;
		void UnbindMesh() const;
		void RenderMesh() const;
	};

}

#endif // _MESH_H
