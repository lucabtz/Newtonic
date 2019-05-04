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

#ifndef _MESH_RENDERER_H
#define _MESH_RENDERER_H

#include "behaviour.h"
#include "mesh.h"
#include "shader.h"
#include <memory>
#include <string>

 namespace Newtonic
 {

   class MeshRenderer : public Behaviour
   {
     std::weak_ptr<Mesh> m_wpMesh;
     std::weak_ptr<Shader> m_wpShader;

   public:
    MeshRenderer(std::weak_ptr<Mesh> wpMesh, std::weak_ptr<Shader> wpShader) :
      m_wpMesh(wpMesh),
      m_wpShader(wpShader)
    {};

     void Update() override;
     void Render() override;
   };

 }

#endif // _MESH_RENDERER_H
