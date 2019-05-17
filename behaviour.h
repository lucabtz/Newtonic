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

#ifndef _BEHAVIOUR_H
#define _BEHAVIOUR_H

 namespace Newtonic
 {
   class Actor;
   class Scene;

   class Behaviour
   {
     Actor * m_actor;

   public:
     /**
      * Sets the actor this behaviour belongs to. To be used internally by newtonic, should NOT be used
      * @param actor a pointer to actor that will be NOT owned by the behaviour
      */
     void SetActor(Actor * actor);
     /**
      * Getter for the actor this behaviour belongs to
      * @return a raw pointer to the actor
      */
     Actor * GetActor();
     /**
      * Getter for the scene this behaviour's actor is in
      * @return a raw pointer to the scene
      */
     Scene * GetScene();

     /**
      * Inits the behaviour
      */
     virtual void Init() = 0;
     /**
      * Updates the behaviour
      * @param dt the time ellapsed from previous update
      */
     virtual void Update(float dt) = 0;
     /**
      * Renders what the behaviour is supposed to render
      */
     virtual void Render() = 0;
   };
 }

#endif // _BEHAVIOUR_H
