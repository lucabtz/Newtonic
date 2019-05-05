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

#include "scene.h"
#include "actor.h"

 namespace Newtonic
 {

   void Scene::AddActor(std::shared_ptr<Actor> actor)
   {
      m_actors.push_back(std::move(actor));
   }

   void Scene::Render()
   {
     for (auto & actor : m_actors)
     {
       actor->Render();
     }
   }

   void Scene::Update()
   {
     for (auto & actor : m_actors)
     {
       actor->Update();
     }
   }

 }
