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

#include "actor.h"
#include "mesh.h"
#include "camera.h"
#include "scene.h"
#include "assets.h"
#include "engine.h"
#include "transform.h"
#include "mesh_shader.h"

#include <glm/glm.hpp>

 namespace Newtonic
 {
   void MeshRenderer::Init()
   {
     m_wpCamera = GetScene()->GetCamera();
     m_wpMesh = g_engine->GetAssetsManager()->GetMesh(m_meshName);
     m_wpShader = g_engine->GetAssetsManager()->GetShaderT<MeshShader>(m_shaderName);
     m_wpActorTransform = GetActor()->GetTransform();
   }

   void MeshRenderer::Render()
   {
     auto pMesh = m_wpMesh.lock();
     auto pShader = m_wpShader.lock();
     auto pTransform = m_wpActorTransform.lock();
     auto pCamera = m_wpCamera.lock();
     if (pMesh && pShader && pTransform && pCamera)
     {
       pShader->UseShader();
       pShader->SetModel(pTransform->GetTransformationMatrix());
       pShader->SetView(pCamera->GetView());
       pShader->SetProj(pCamera->GetProjection());
       pMesh->BindMesh();
       pMesh->RenderMesh();
       pMesh->UnbindMesh();
       pShader->StopShader();
     }
   }
 }
