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

 #ifndef _SIMPLE_CAMERA_MOVER_H
 #define _SIMPLE_CAMERA_MOVER_H

 #include <memory>

 #include "behaviour.h"

 namespace Newtonic
 {
   class Actor;
   class Camera;
   class Input;

   std::shared_ptr<Actor> MakeSimpleCameraMover(float speed);

   class SimpleCameraMoverBehaviour : public Behaviour
   {
     std::weak_ptr<Camera> m_wpCamera;
     Input * m_pInput;
     Scene * m_pScene;

     float m_speed;

   public:
     SimpleCameraMoverBehaviour(float speed) : m_speed(speed) {}
     void Init() override;
     void Render() override {};
     void Update(float dt) override;
   };
 }

 #endif // _SIMPLE_CAMERA_MOVER_H
