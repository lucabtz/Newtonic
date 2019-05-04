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

#include "mesh_renderer.h"
#include "assets.h"


 namespace Newtonic
 {

   void MeshRenderer::Update()
   {}

   void MeshRenderer::Render()
   {
     auto pMesh = m_wpMesh.lock();
     auto pShader = m_wpShader.lock();
     if (pMesh && pShader)
     {
       glUseProgram(pShader->GetShaderId());

       glEnableVertexAttribArray(0);

       glBindBuffer(GL_ARRAY_BUFFER, pMesh->GetPositionsVBO());
       glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
       glDrawArrays(GL_TRIANGLES, 0, pMesh->GetVertexCount());

       glDisableVertexAttribArray(0);
     }
   }


 }
