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

#ifndef _SCENE_H
#define _SCENE_H

#include <vector>
#include <memory>
#include <iostream>

#include "camera.h"

 namespace Newtonic
 {
   class Actor;

   class Scene
   {
     std::vector<std::shared_ptr<Actor>> m_actors;
     std::shared_ptr<Camera> m_camera;

   public:

     Scene()
     {
       m_camera = std::make_shared<Camera>();
     }

     ~Scene() { std::cout << "[SCENE] Deleting scene " << this << std::endl; }

     void AddActor(std::shared_ptr<Actor> && actor);
     void Render();
     void Update();

     std::weak_ptr<Camera> GetCamera() const
     {
       return m_camera;
     }
   };

 }

#endif // _SCENE_H
